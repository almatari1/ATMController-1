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
 * sample_bank.cc
 *
 *  Created on: Mar 4, 2021
 *      Author: ashish
 *
 *  Description: A Sample Bank definition.
 *               Note: This is only to simulate bank account transactions.
 */


#include "../include/sample_bank.h"

// Sample bank methods
BankApiResponseStatus SampleBank::authenticate_card(const string card_number) {
  return BankApiResponseStatus::kBankApiAuthenticationSuccessful;
}

BankApiResponseStatus SampleBank::authenticate_pin(const string & pin) {
  return ((pin == pin_) ?
      BankApiResponseStatus::kBankApiAuthenticationSuccessful :
      BankApiResponseStatus::kBankApiAuthenticationFailed);
}

BankApiResponseStatus SampleBank::deposit(const AccountType account_type, const long amount) {

  BankApiResponseStatus response_status = BankApiResponseStatus::kBankApiTransactionSuccessful;

  if (account_type == AccountType::kChecking) {
    checking_balance_ += amount;
  } else if (account_type == AccountType::kSavings) {
    savings_balance_ += amount;
  } else {
    response_status = BankApiResponseStatus::kBankApiTransactionUnsupported;
  }

  return response_status;
}

BankApiResponseStatus SampleBank::withdraw(const AccountType account_type, const long amount) {

  BankApiResponseStatus response_status = BankApiResponseStatus::kBankApiTransactionSuccessful;

  if (account_type == AccountType::kChecking) {
    if (checking_balance_ >= amount) {
      checking_balance_ -= amount;
    } else {
      response_status = BankApiResponseStatus::kBankApiInsufficientFunds;
    }
  } else if (account_type == AccountType::kSavings) {
    if (savings_balance_ >= amount) {
      savings_balance_ -= amount;
    } else {
      response_status = BankApiResponseStatus::kBankApiInsufficientFunds;
    }
  } else {
    response_status = BankApiResponseStatus::kBankApiTransactionUnsupported;
  }

  return response_status;
}

BankApiResponseStatus SampleBank::get_balance(const AccountType account_type, long & balance) {

  BankApiResponseStatus response_status = BankApiResponseStatus::kBankApiTransactionSuccessful;

  if (account_type == AccountType::kChecking) {
    balance = checking_balance_;
  } else if (account_type == AccountType::kSavings) {
    balance = savings_balance_;
  } else {
    response_status = BankApiResponseStatus::kBankApiTransactionUnsupported;
  }

  return response_status;
}
