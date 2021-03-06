/*
 * Copyright (C) 2021, Ashish Naik
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*
 * atm_controller.cc
 *
 *  Created on: Feb 25, 2021
 *      Author: ashish
 *
 *  Description: ATM Controller implementation.
 */

#include <iostream>
#include "../include/atm_controller.h"
#include "../include/atm_hardware_factory.h"
#include "../include/io_factory.h"


namespace atmcontroller {

  using std::to_string;
  using namespace atmhardwarefactory;
  using namespace iofactory;

  // global const in this namespace
  extern const unsigned short kMaxPinTries {3};

  // Class methods
  ATMController::ATMController(OperatingMode mode):
      operating_mode_(mode) {

    // interface pointers
    server_connection_ptr_ = NULL;
    atm_hardware_interface_ = NULL;
    io_interface_ = NULL;
    bank_api_ = NULL;

    // next state of the controller
    next_state_ = ControllerState::kControllerStateOff;
    // account type selected by the user
    selected_account_type_ = AccountType::kInvalidAccountType;

    // flags
    is_initialized_ = false;
    card_inserted_ = false;
    stop_service_ = false;
  }

  ATMController::~ATMController() {
  }

  void ATMController::switch_on() {

    std::clog << "Switching On ATM Controller...\n";
    // initialize the ATM Controller
    initialize();

    if (is_initialized_) {
      next_state_ = ControllerState::kControllerStateOn;
      stop_service_ = false;
      // server customers
      serve();
    } else {
      std::cerr << "Unable to initialize ATM Controller. Switching Off...\n";
      switch_off();
    }
  }

  //
  // private member functions
  //

  void ATMController::switch_off() {
    // de-initialize the ATM Controller
    deinitialize();
  }


  // ATM Controller initialization
  void ATMController::initialize() {

    bool hardware_initialized = false;
    bool io_initialized = false;
    bool server_initialized = false;

    // initialize ATM hardware interface
    atm_hardware_interface_ = ATMHardwareFactory::GetATMHardwareInterface();

    if (atm_hardware_interface_) {
      hardware_initialized = true;
    } else {
      std::cerr << "Unable To Initialize ATM Hardware Interface\n";
    }

    // initialize IO
    io_interface_ = IOFactory::GetIOInterface();
    if (io_interface_) {
      io_initialized = true;
    } else {
      std::cerr << "Unable To Initialize ATM Hardware Interface\n";
    }

    // initialize bank server connection
    try {
      server_connection_ptr_ = new BankServerConnection();
      server_initialized = true;
    }
    catch (std::bad_alloc &ba) {
      std::cerr << "Connection Error: Could not establish server connection\n";
      std::cerr << "bad_alloc caught: " << ba.what() << "\n";
    }

    // set the is_initialized_ flag
    is_initialized_ =  hardware_initialized && io_initialized && server_initialized;
  }

  // ATM Controller de-initialization
  void ATMController::deinitialize() {
    // disconnect bank and terminate server connection
    delete_bank_connection();
    delete_server_connection();
    delete_io_interface();
    delete_atm_hardware_interface();
    is_initialized_ = false;
  }

  void ATMController::delete_bank_connection() {
    if (server_connection_ptr_) {
      if (bank_api_) {
        server_connection_ptr_->DisconnectBank(bank_api_);
        delete bank_api_;
        bank_api_ = NULL;
      }
    }
  }

  void ATMController::delete_server_connection() {
    if (server_connection_ptr_) {
      delete server_connection_ptr_;
      server_connection_ptr_ = NULL;
    }
  }

  void ATMController::delete_io_interface() {
    if (io_interface_) {
      delete io_interface_;
      io_interface_ = NULL;
    }
  }

  void ATMController::delete_atm_hardware_interface() {
    if (atm_hardware_interface_) {
      delete atm_hardware_interface_;
      atm_hardware_interface_ = NULL;
    }
  }

  // validate whether input string is numeric and return numeric value if so
  bool ATMController::validate_and_convert_numeric(
      const string & numeric_str, long & numeric_val) {

    bool is_valid = false;
    if (is_numeric(numeric_str)) {
      try{
        numeric_val = stol(numeric_str);
        is_valid = true;
      }
      catch (std::invalid_argument &ia) {
        std::cerr << "Exception in ATMController::validate_and_convert_numeric(...)\n";
        std::cerr << "invalid_argument caught: " << ia.what() << "\n";
      }
      catch (std::out_of_range &oor) {
        std::cerr << "Exception in ATMController::validate_and_convert_numeric(...)\n";
        std::cerr << "out_of_range caught: " << oor.what() << "\n";
        io_interface_->display_message("Amount cannot be greater than 9,223,372,036,854,775,807\n");
      }
    }
    return is_valid;
  }

  // check whether input string is numeric
  bool ATMController::is_numeric(const string & str) {
    bool is_numeric_str = true;
    for (unsigned int i = 0; i < str.length(); ++i) {
      if (isdigit(str[i]) == false){
        is_numeric_str = false;
        break;
      }
    }
    return is_numeric_str;
  }

  // this is the main service loop
  void ATMController::serve() {

    while (!stop_service_) {

      switch (next_state_) {

      case ControllerState::kControllerStateSwitchOff:
        next_state_ = handle_switch_off_state();
        break;

      case ControllerState::kControllerStateOn:
        next_state_ = handle_on_state();
        break;

      case ControllerState::kControllerStateMainMenu :
        // now that the controller is on, start serving customers
        next_state_ = handle_main_menu_state();
        break;

      case ControllerState::kControllerStateAcceptCard:
        next_state_ = handle_accept_card_state();
        break;

      case ControllerState::kControllerStateAcceptPin:
        next_state_ = handle_accept_pin_state();
        break;

      case ControllerState::kControllerStateAccountSelection:
        next_state_ = handle_account_selection_state();
        break;

      case ControllerState::kControllerStateTransact:
        next_state_ = handle_transact_state();
       break;

      case ControllerState::kControllerStateEjectCard:
        next_state_ = handle_eject_card_state();
        break;

      default:
        io_interface_->display_message("ATM Controller Entered Unknown State... Stopping Service\n");
        stop_service_ = true;
        break;

      } // switch (next_state_)
    } // while (stop_service_ == false)
  }

  ControllerState ATMController::handle_on_state() {
    io_interface_->switch_on();
    stop_service_ = false;
    // start serving customers
    return ControllerState::kControllerStateMainMenu;
  }

  ControllerState ATMController::handle_switch_off_state() {
    stop_service_ = true;
    io_interface_->switch_off();
    // switch the controller oof
    switch_off();
    return ControllerState::kControllerStateOff;
  }

  ControllerState ATMController::handle_main_menu_state() {

    ControllerState next_state = next_state_;
    card_inserted_ = false;
    selected_account_type_ = AccountType::kInvalidAccountType;

    UserSelection user_choice = io_interface_->main_menu_wait();

    // Start ATM transactions
    if (user_choice == UserSelection::kUserSelectionStart) {
      next_state = ControllerState::kControllerStateAcceptCard;
    } else {
      next_state = ControllerState::kControllerStateSwitchOff;
    }
    return next_state;
  }

  ControllerState ATMController::handle_accept_card_state() {

    ControllerState next_state = ControllerState::kControllerStateEjectCard;;
    bool card_authenticated = false;

    // get card input from user
    UserSelection user_choice = io_interface_->get_card_input();

    // simulate card-insertion
    if (user_choice == UserSelection::kUserSelectionCardInserted) {
      card_inserted_ = true;
      string card_number;

      if ((ATMHardwareStatus::kAtmHwSuccess == atm_hardware_interface_->get_card_number(card_number))) {
        // connect to appropriate Bank
        if (server_connection_ptr_) {
          string bank_id = server_connection_ptr_->GetBankIDFromCard(card_number);
          bank_api_ = server_connection_ptr_->ConnectToBank(bank_id);
          if (bank_api_) {
            // authenticate card
            if ((BankApiResponseStatus::kBankApiAuthenticationSuccessful == bank_api_->authenticate_card(card_number))) {
              // set card_authenticated flag
              card_authenticated = true;
            } else {
              io_interface_->display_message("Card Authentication Failed! Please try again...\n");
            }
          } else {
            io_interface_->display_message("Connection Error: Could not connect to the bank. Please try again...\n");
          }
        } else {
          io_interface_->display_message("Connection Error: No Server Connection\n");
        }
      } else {
        io_interface_->display_message("Unable To read card. Please try again...\n");
      }
    }  // if (user_choice == UserSelection::kUserSelectionCardInserted)

    if (card_authenticated) {
      // go to next step - accept pin
      next_state = ControllerState::kControllerStateAcceptPin;
    }

    return next_state;
  }

  ControllerState ATMController::handle_accept_pin_state() {

    ControllerState next_state = next_state_;

    unsigned short pin_tries = 0;
    bool pin_authenticated = false;
    bool cancel_transaction = false;
    string pin;

    do {
      // get user pin
      UserSelection user_choice = io_interface_->get_user_pin(pin);

      // if user chose to cancel, do so
      if (user_choice == UserSelection::kUserSelectionCancel) {
        io_interface_->display_message("Cancelled\n");
        cancel_transaction = true;

      } else if (user_choice == UserSelection::kUserSelectionPinEntered) {  // user entered pin
        // authenticate pin
        if (validate_pin(pin) &&
            (BankApiResponseStatus::kBankApiAuthenticationSuccessful == bank_api_->authenticate_pin(pin))) {
          pin_authenticated = true;
        } else {  // track number of pin tries
          pin_tries += 1;
          string display_msg = "Invalid PIN... PIN Must Be 4-digit Numeric \nTries left: " + to_string(kMaxPinTries-pin_tries) + "\n";
          io_interface_->display_message(display_msg);
        }

      } else {  // consider this as an invalid transaction and cancel
        io_interface_->display_message("Invalid Selection\n");
        cancel_transaction = true;
      }
    } while (!cancel_transaction && !pin_authenticated && pin_tries < kMaxPinTries);

    // if cancelled or pin authentication fails, eject the card and go to main menu
    if (pin_authenticated) {
      next_state = ControllerState::kControllerStateAccountSelection;
    } else {
      next_state = ControllerState::kControllerStateEjectCard;
    }

    return next_state;
  }

  ControllerState ATMController::handle_eject_card_state() {

    if (card_inserted_) {
      ATMHardwareStatus status = atm_hardware_interface_->eject_card();
      // assumes that the atm stored the card and
      // card slot is vacant for next card
      card_inserted_ = false;
      //disconnect from bank
      delete_bank_connection();
      selected_account_type_ = AccountType::kInvalidAccountType;

      if (ATMHardwareStatus::kAtmHwSuccess == status) {
        io_interface_->notify_card_ejection();
      } else {
        io_interface_->display_message("Unable to eject card... Please contact your Bank\n");
      }
    }

    return ControllerState::kControllerStateMainMenu;
  }

  ControllerState ATMController::handle_account_selection_state() {

    ControllerState next_state = ControllerState::kControllerStateEjectCard;
    UserSelection user_choice = io_interface_->get_account_type();

    // select the next state based on user choice
    if (user_choice == UserSelection::kUserSelectionCheckingAccount) {
      selected_account_type_ = AccountType::kChecking;
      next_state = ControllerState::kControllerStateTransact;

    } else if (user_choice == UserSelection::kUserSelectionSavingsAccount) {
      selected_account_type_ = AccountType::kSavings;
      next_state = ControllerState::kControllerStateTransact;

    } else if (user_choice == UserSelection::kUserSelectionCancel) {
      io_interface_->display_message("Cancelled\n");
      selected_account_type_ = AccountType::kInvalidAccountType;
      next_state = ControllerState::kControllerStateEjectCard;

    } else { // Cancel or any other choice
      io_interface_->display_message("Unsupported or Invalid Account Type\n");
      selected_account_type_ = AccountType::kInvalidAccountType;
      next_state = ControllerState::kControllerStateEjectCard;
    }

    return next_state;
  }

  ControllerState ATMController::handle_transact_state() {

    // be in the same transaction state till the user selects otherwise
    ControllerState next_state = next_state_;
    bool more_transactions = true;

    do {

      UserSelection user_choice = io_interface_->get_atm_transaction();

      switch (user_choice) {

      case UserSelection::kUserSelectionCheckBalance:{
        long balance;
        BankApiResponseStatus response_status = bank_api_->get_balance(selected_account_type_, balance);
        if (BankApiResponseStatus::kBankApiTransactionSuccessful ==  response_status) {
          io_interface_->notify_balance(balance);
        } else {
          io_interface_->display_message("Transaction Failed... Please try again\n");
        }
      } break;

      case UserSelection::kUserSelectionDeposit: {

        string amount_str;
        UserSelection deposit_choice = io_interface_->get_amount(amount_str);

        if (deposit_choice == UserSelection::kUserSelectionConfirm) {

          long amount;
          // validate the amount and get numeric value
          if (validate_and_convert_numeric(amount_str, amount)){

            ATMHardwareStatus atm_hw_status;
            BankApiResponseStatus bank_response_status;

            // prepare ATM Hardware to deposit cash in the machine
            atm_hw_status = atm_hardware_interface_->prepare_to_deposit_cash(amount);
            if (ATMHardwareStatus::kAtmHwSuccess == atm_hw_status) {
              // update deposit amount in the bank
              bank_response_status = bank_api_->deposit(selected_account_type_, amount);

            } else if (ATMHardwareStatus::kAtmHwAmountMismatch == atm_hw_status) {
              io_interface_->display_message("Amount MISMATCH\n");

            } else {
              io_interface_->display_message("Unable to deposit cash... Sorry for the inconvenience\n");
            }

            if (ATMHardwareStatus::kAtmHwSuccess == atm_hw_status &&
                BankApiResponseStatus::kBankApiTransactionSuccessful ==  bank_response_status) {
              atm_hardware_interface_->deposit_cash();
              io_interface_->display_message("Deposit SUCCESSFUL\n");

            } else {
              // cancel and return the cash deposit
              atm_hardware_interface_->eject_cash_deposit();
              io_interface_->display_message("Deposit FAILED... Please collect your cash");
            }

          } else {
            io_interface_->display_message("Please Enter a Valid Amount\n");
          }
        } else {
          io_interface_->display_message("Cancelled\n");
        }
      } break;

      case UserSelection::kUserSelectionWithdraw: {
        string amount_str;
        UserSelection withdrawal_choice = io_interface_->get_amount(amount_str);

        if (withdrawal_choice == UserSelection::kUserSelectionConfirm) {

          long numeric_amount;
          // validate the amount and get numeric value
          if (validate_and_convert_numeric(amount_str, numeric_amount)){

            ATMHardwareStatus atm_hw_status;
            BankApiResponseStatus bank_response_status;
            bool withdrawal_successful = false;

            // prepare ATM Hardware to deposit cash in the machine
            atm_hw_status = atm_hardware_interface_->prepare_to_dispense_cash(numeric_amount);
            if (ATMHardwareStatus::kAtmHwSuccess == atm_hw_status) {
              // update deposit amount in the bank
              bank_response_status = bank_api_->withdraw(selected_account_type_, numeric_amount);
              if (BankApiResponseStatus::kBankApiTransactionSuccessful ==  bank_response_status) {
                atm_hardware_interface_->dispense_cash();
                withdrawal_successful = true;

              } else if (BankApiResponseStatus::kBankApiInsufficientFunds ==  bank_response_status) {
                io_interface_->display_message("Insufficient Account Balance\n");
              }

            } else if (ATMHardwareStatus::kAtmHwInsufficientCash == atm_hw_status) {
              io_interface_->display_message("Insufficient cash in ATM... Please try smaller amount\n");

            } else {
              io_interface_->display_message("Unable to dispense cash... Sorry for the inconvenience\n");
            }

            // notify user
            if (withdrawal_successful) {
              io_interface_->notify_money_dispensed();
            } else {
              // cancel and return the cash deposit
              atm_hardware_interface_->cancel_cash_dispense();
              io_interface_->display_message("Withdrawal FAILED\n");
            }

          } else {
            io_interface_->display_message("Please Enter a Valid Amount\n");
          }
        } else {
          io_interface_->display_message("Cancelled\n");
        }

      } break;

      case UserSelection::kUserSelectionBack:
        next_state = ControllerState::kControllerStateAccountSelection;
        more_transactions = false;
        break;

      case UserSelection::kUserSelectionCancel:
        next_state = ControllerState::kControllerStateEjectCard;
        more_transactions = false;
        break;

      default:
        // eject card and go back to main menu
        next_state = ControllerState::kControllerStateEjectCard;
        more_transactions = false;
      }

    } while (more_transactions);

    return next_state;
  }

} // namespace atmcontroller
