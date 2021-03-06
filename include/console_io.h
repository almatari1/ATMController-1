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
 * console_io.h
 *
 *  Created on: Feb 25, 2021
 *      Author: ashish
 *
 *  Description: Class definition for console IO.
 */

#ifndef INCLUDE_CONSOLE_IO_H_
#define INCLUDE_CONSOLE_IO_H_

#include <iostream>
#include "io_interface.h"

using namespace iointerface;
using std::cout;

class ConsoleIO: public IOInterface {
public:
  ConsoleIO(){}
  ~ConsoleIO(){}

  UserSelection main_menu_wait();
  UserSelection get_card_input();
  UserSelection get_user_pin(string & pin);
  UserSelection get_account_type();
  UserSelection get_atm_transaction();
  UserSelection get_amount(string & amount);

  inline bool switch_on() {cout << "\nWelcome!\n"; return true;}
  inline void switch_off() {cout << "\nGoodbye!\n";}
  inline void display_message(const string msg) {cout << msg;}
  inline void notify_balance(const long balance) {cout << "Account Balance: " << balance << "\n";}
  inline void notify_card_ejection() {cout << "\nPlease collect your card\n";}
  inline void notify_money_dispensed() {cout << "\nPlease collect your money\n";}
};

#endif /* INCLUDE_CONSOLE_IO_H_ */
