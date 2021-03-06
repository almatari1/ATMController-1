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
 * sample_bank.h
 *
 *  Created on: Mar 4, 2021
 *      Author: ashish
 *
 *  Description: A Sample Bank definition.
 *               Note: This is only to simulate bank transactions.
 */

#ifndef INCLUDE_SAMPLE_BANK_H_
#define INCLUDE_SAMPLE_BANK_H_

#include <string>

#include "atm_common_defs.h"
#include "bank_api.h"

using namespace atmcommondefs;
using namespace bankapi;
using std::string;


/* A test bank for verifying ATM Controller functionality */
class SampleBank: public BankAPI {
  long checking_balance_;
  long savings_balance_;
  string pin_;  // 4-digit pin

public:
  SampleBank(long initial_checking_balance=kDefaultInitialCheckingBalance,
      long initial_savings_balance=kDefaultInitialSavingsBalance,
      string pin=kDefaultPin){
    checking_balance_ = initial_checking_balance;
    savings_balance_ = initial_savings_balance;
    pin_ = pin;
  }
  ~SampleBank(){}

  BankApiResponseStatus authenticate_card(const string card_number);
  BankApiResponseStatus authenticate_pin(const string & pin);
  BankApiResponseStatus deposit(const AccountType account_type, const long amount);
  BankApiResponseStatus withdraw(const AccountType account_type, const long amount);
  BankApiResponseStatus get_balance(const AccountType account_type, long & balance);

};

#endif /* INCLUDE_SAMPLE_BANK_H_ */
