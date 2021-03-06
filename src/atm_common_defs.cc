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
 * atm_common_defs.cc
 *
 *  Created on: Feb 25, 2021
 *      Author: ashish
 *
 *  This file contains common definitions used by the ATM Controller.
 */

#include "../include/atm_common_defs.h"

namespace atmcommondefs {

  // constants and defaults definitions
  extern const string kDefaultCardNumber {"1111111111111111"};
  extern const string kDefaultBankId {kDefaultCardNumber.substr(0,4)};  // bank id assumed as first 4 digits of card number
  extern const string kDefaultPin {"1234"};
  extern const unsigned long kDefaultInitialCheckingBalance {1000};
  extern const unsigned long kDefaultInitialSavingsBalance {1000};

}
