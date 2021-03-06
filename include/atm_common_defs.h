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
 * atm_common_defs.h
 *
 *  Created on: Feb 25, 2021
 *      Author: ashish
 *
 *  Description: Common definitions used by the ATM Controller.
 */

#ifndef INCLUDE_ATM_COMMON_DEFS_H_
#define INCLUDE_ATM_COMMON_DEFS_H_

#include <string>

namespace atmcommondefs {

  using std::string;

  //
  // constants and defaults
  //

  // default atm card number
  extern const string kDefaultCardNumber;
  // default bank id
  extern const string kDefaultBankId;
  // default atm card pin
  extern const string kDefaultPin;
  // default initial checking account balance
  extern const unsigned long kDefaultInitialCheckingBalance;
  // default initial savings account balance
  extern const unsigned long kDefaultInitialSavingsBalance;

} // namespace atmcommondefs

#endif /* INCLUDE_ATM_COMMON_DEFS_H_ */
