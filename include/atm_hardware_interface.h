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
 * atm_hardware_interface.h
 *
 *  Created on: Mar 4, 2021
 *      Author: ashish
 *
 *  Description: ATM Hardware Interface definition.
 */

#ifndef INCLUDE_ATM_HARDWARE_INTERFACE_H_
#define INCLUDE_ATM_HARDWARE_INTERFACE_H_

#include <string>

namespace atmhardwareinterface {

  using std::string;

  enum class ATMHardwareStatus {
    kAtmHwFailure = 0,
    kAtmHwSuccess,
    kAtmHwMalFunction,
    kAtmHwInsufficientCash,
    kAtmHwAmountMismatch
  };

  // ATM Hardware Interface
  class ATMHardwareInterface {
  public:
    virtual ~ATMHardwareInterface() = 0;
    virtual ATMHardwareStatus get_card_number(string &) = 0;
    virtual ATMHardwareStatus eject_card() = 0;

    // below two "prepare_to_" methods:
    // 1. are allowed fail
    // 2. if successful, should put the atm hardware in a state
    //    that guarantees cash deposit/eject cash deposit and
    //    cash dispense/cancel cash dispense operations respectively.
    virtual ATMHardwareStatus prepare_to_deposit_cash(const long) = 0;
    virtual ATMHardwareStatus prepare_to_dispense_cash(const long) = 0;

    // below four methods Must Always Succeed
    virtual ATMHardwareStatus deposit_cash() = 0;
    virtual ATMHardwareStatus eject_cash_deposit() = 0;
    virtual ATMHardwareStatus dispense_cash() = 0;
    virtual ATMHardwareStatus cancel_cash_dispense() = 0;

  };

} // namespace atmhardwareinterface

#endif /* INCLUDE_ATM_HARDWARE_INTERFACE_H_ */
