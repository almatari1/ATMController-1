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
 * io_interface.h
 *
 *  Created on: Mar 5, 2021
 *      Author: ashish
 *
 *  Description: IO interface definition.
 */

#ifndef INCLUDE_IO_INTERFACE_H_
#define INCLUDE_IO_INTERFACE_H_

#include <string>

namespace iointerface {

  using std::string;

  enum class UserSelection {
    kUserSelectionInvalid = 0,
    kUserSelectionExit,
    kUserSelectionStart,
    kUserSelectionBack,
    kUserSelectionCancel,
    kUserSelectionConfirm,
    kUserSelectionMainMenu,
    kUserSelectionCardInserted,
    kUserSelectionPinEntered,
    kUserSelectionCheckingAccount,
    kUserSelectionSavingsAccount,
    kUserSelectionCheckBalance,
    kUserSelectionDeposit,
    kUserSelectionWithdraw,
    kUserSelectionNoMoreTransactions
  };


  class IOInterface {
  public:
    virtual ~IOInterface() = 0;

    virtual UserSelection main_menu_wait() = 0;
    virtual UserSelection get_card_input() = 0;
    virtual UserSelection get_user_pin(string & pin) = 0;
    virtual UserSelection get_account_type() = 0;
    virtual UserSelection get_atm_transaction() = 0;
    virtual UserSelection get_amount(string & amount) = 0;

    virtual bool switch_on() = 0;
    virtual void switch_off() = 0;
    virtual void display_message(const string msg) = 0;
    virtual void notify_balance(const long balance) = 0;
    virtual void notify_card_ejection() = 0;
    virtual void notify_money_dispensed() = 0;

  };

} // namespace iointerface

#endif /* INCLUDE_IO_INTERFACE_H_ */
