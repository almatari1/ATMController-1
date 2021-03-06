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
 * bank_api.h
 *
 *  Created on: Feb 25, 2021
 *      Author: ashish
 *
 *  Description: Bank API definition.
 */

#ifndef INCLUDE_BANK_API_H_
#define INCLUDE_BANK_API_H_

#include <string>

namespace bankapi {

  using std::string;

  enum class AccountType {
    kInvalidAccountType = 0,
    kChecking,
    kSavings
  };

  enum class BankApiResponseStatus {
    kBankApiTransactionFailed = 0,
    kBankApiTransactionSuccessful,
    kBankApiTransactionInvalid,
    kBankApiTransactionUnsupported,
    kBankApiAuthenticationSuccessful,
    kBankApiAuthenticationFailed,
    kBankApiInsufficientFunds
  };

  /* Bank API Interface*/
  class BankAPI {
  public:
    virtual ~BankAPI() = 0;
    virtual BankApiResponseStatus authenticate_card(const string card_number) = 0;
    virtual BankApiResponseStatus authenticate_pin(const string & pin) = 0;
    virtual BankApiResponseStatus deposit(const AccountType account_type, const long amount) = 0;
    virtual BankApiResponseStatus withdraw(const AccountType account_type, const long amount) = 0;
    virtual BankApiResponseStatus get_balance(const AccountType account_type, long & balance) = 0;
  };

  // Overloaded equality operator for the defined Enum
  bool operator == (const int &i, const AccountType &account_type);

} // namespace bankapi

#endif /* INCLUDE_BANK_API_H_ */
