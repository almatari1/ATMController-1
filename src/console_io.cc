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
 * console_io.cc
 *
 *  Created on: Feb 25, 2021
 *      Author: ashish
 *
 *  Description: Console IO implementation.
 */


#include "../include/console_io.h"

using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::string;

// waits on main menu for user input
UserSelection ConsoleIO::main_menu_wait() {

  string user_input;
  UserSelection user_choice = UserSelection::kUserSelectionInvalid;

  do {
    cout << "\n\nMain Menu\n\n";
    cout << "Press: \n1 Start \n2 Exit Controller\n";
    cin >> user_input;

    if (user_input == "1") {
      user_choice = UserSelection::kUserSelectionStart;
    } else if (user_input == "2") {
      user_choice = UserSelection::kUserSelectionExit;
    } else {
      user_choice = UserSelection::kUserSelectionInvalid;
      cout << "Please enter a valid choice\n";
    }

  } while (user_choice == UserSelection::kUserSelectionInvalid);

  return user_choice;
}

// simulates card input
UserSelection ConsoleIO::get_card_input() {

  string user_input;
  UserSelection user_choice = UserSelection::kUserSelectionInvalid;

  do {
    cout << "\nPlease Insert Card\n";
    cout << "Select: \n1 Simulate card insertion \n2 Back To Main Menu\n";
    cin >> user_input;

    if (user_input == "1") {
      user_choice = UserSelection::kUserSelectionCardInserted;
    } else if (user_input == "2") {
      user_choice = UserSelection::kUserSelectionBack;
    } else {
      user_choice = UserSelection::kUserSelectionInvalid;
      cout << "Please enter a valid choice\n";
    }
  } while (user_choice == UserSelection::kUserSelectionInvalid);

  return user_choice;
}

// get car pin from user
UserSelection ConsoleIO::get_user_pin(string & pin) {

  string user_input;
  UserSelection user_choice = UserSelection::kUserSelectionInvalid;

  cout << "\nEnter 4-digit PIN:\n";
  cout << "(Enter 0 to Cancel)\n";
  cin >> user_input;

  if (user_input == "0") {
    user_choice = UserSelection::kUserSelectionCancel;
  } else {
    pin = user_input;
    user_choice = UserSelection::kUserSelectionPinEntered;
  }

  return user_choice;
}

// gets account type selection from user
UserSelection ConsoleIO::get_account_type() {

  string user_input;
  UserSelection user_choice = UserSelection::kUserSelectionInvalid;

  do {
    cout << "\nSelect Account:\n";
    cout << "1 Checking \n2 Savings \n3 Cancel\n";
    cin >> user_input;

    if (user_input == "1") {
      user_choice = UserSelection::kUserSelectionCheckingAccount;
    } else if (user_input == "2") {
      user_choice = UserSelection::kUserSelectionSavingsAccount;
    } else if (user_input == "3") {
      user_choice = UserSelection::kUserSelectionCancel;
    } else {
      user_choice = UserSelection::kUserSelectionInvalid;
      cout << "Please enter a valid choice\n";
    }
  } while (user_choice == UserSelection::kUserSelectionInvalid);

  return user_choice;

}

// gets the atm transaction user wants to perform
UserSelection ConsoleIO::get_atm_transaction() {

    string user_input;
    UserSelection user_choice = UserSelection::kUserSelectionInvalid;

    do {
      cout << "\nSelect Transaction:\n";
      cout << "1 Balance \n2 Deposit \n3 Withdraw \n4 Back \n5 Cancel" << endl;
      cin >> user_input;

      if (user_input == "1") {
        user_choice = UserSelection::kUserSelectionCheckBalance;
      } else if (user_input == "2") {
        user_choice = UserSelection::kUserSelectionDeposit;
      } else if (user_input == "3") {
        user_choice = UserSelection::kUserSelectionWithdraw;
      } else if (user_input == "4") {
        user_choice = UserSelection::kUserSelectionBack;
      } else if (user_input == "5") {
        user_choice = UserSelection::kUserSelectionCancel;
      } else {
        user_choice = UserSelection::kUserSelectionInvalid;
        cout << "Please enter a valid choice\n";
      }
    } while (user_choice == UserSelection::kUserSelectionInvalid);

    return user_choice;
}

// get the amount user wants to deposit/withdraw
UserSelection ConsoleIO::get_amount(string &amount) {

  string user_input;
  UserSelection user_choice = UserSelection::kUserSelectionInvalid;

  do {
    cout << "Amount: " << endl;
    cin >> amount;
    cout << "\nSelect: \n1 Confirm \n2 Cancel" << endl;
    cin >> user_input;

    // check for confirmation
    if (user_input == "1") {
      user_choice = UserSelection::kUserSelectionConfirm;
    } else if (user_input == "2") {
      user_choice = UserSelection::kUserSelectionCancel;
    } else {
      user_choice = UserSelection::kUserSelectionInvalid;
      cout << "Please enter a valid choice\n";
    }

  } while (user_choice == UserSelection::kUserSelectionInvalid);

  return user_choice;
}
