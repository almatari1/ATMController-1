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
 * atm_controller.h
 *
 *  Created on: Feb 25, 2021
 *      Author: ashish
 *
 *  Description: ATM Controller definition.
 */

#ifndef INCLUDE_ATM_CONTROLLER_H_
#define INCLUDE_ATM_CONTROLLER_H_

#include <iostream>
#include <string>

#include "atm_common_defs.h"
#include "bank_server_connection.h"
#include "atm_hardware_interface.h"
#include "io_interface.h"
#include "bank_api.h"

namespace atmcontroller {

  using namespace atmhardwareinterface;
  using namespace iointerface;
  using namespace bankapi;
  using std::string;
  using std::stol;

  enum class ControllerState {
    kControllerStateSwitchOff = 0,
    kControllerStateOff,
    kControllerStateOn,
    kControllerStateMainMenu,
    kControllerStateAcceptCard,
    kControllerStateAcceptPin,
    kControllerStateAccountSelection,
    kControllerStateTransact,
    kControllerStateEjectCard
  };

  enum class OperatingMode {
    kOperatingModeTest = 0,
    kOperatingModeServe
  };


  extern const unsigned short kMaxPinTries;

  class ATMController {

    // private members
    BankServerConnection * server_connection_ptr_;
    ATMHardwareInterface * atm_hardware_interface_;
    IOInterface * io_interface_;
    BankAPI * bank_api_;

    OperatingMode operating_mode_;
    ControllerState next_state_;
    AccountType selected_account_type_;

    // flags
    bool is_initialized_;
    bool card_inserted_;
    bool stop_service_;

    // private methods
    void initialize();
    void deinitialize();
    void delete_bank_connection();
    void delete_server_connection();
    void delete_io_interface();
    void delete_atm_hardware_interface();
    void switch_off();
    void serve();

    // state handlers
    ControllerState handle_switch_off_state();
    ControllerState handle_on_state();
    ControllerState handle_main_menu_state();
    ControllerState handle_accept_card_state();
    ControllerState handle_accept_pin_state();
    ControllerState handle_account_selection_state();
    ControllerState handle_transact_state();
    ControllerState handle_eject_card_state();

    bool validate_and_convert_numeric(const string & amount_str, long & amount);
    bool is_numeric(const string &);
    inline bool validate_pin(const string & pin) {return (pin.length() == 4) && is_numeric(pin);}

  public:
    ATMController(OperatingMode mode=OperatingMode::kOperatingModeServe);
    ~ATMController();

    void switch_on();
  };

} // namespace atmcontroller

#endif /* INCLUDE_ATM_CONTROLLER_H_ */
