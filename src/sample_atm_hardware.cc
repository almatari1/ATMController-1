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
 * sample_atm_hardware.cc
 *
 *  Created on: Mar 4, 2021
 *      Author: ashish
 *
 *  Description: A Sample ATM Hardware implementation.
 */

#include "../include/sample_atm_hardware.h"
#include "../include/atm_common_defs.h"

using namespace atmcommondefs;

ATMHardwareStatus SampleATMHardware::get_card_number(string & card_number) {
    card_number = kDefaultCardNumber;
    return ATMHardwareStatus::kAtmHwSuccess;
}

ATMHardwareStatus SampleATMHardware::eject_card() {
    return ATMHardwareStatus::kAtmHwSuccess;
}

ATMHardwareStatus SampleATMHardware::prepare_to_deposit_cash(const long amount) {
  return ATMHardwareStatus::kAtmHwSuccess;
}

ATMHardwareStatus SampleATMHardware::prepare_to_dispense_cash(const long amount) {
  return ATMHardwareStatus::kAtmHwSuccess;
}

ATMHardwareStatus SampleATMHardware::deposit_cash() {
    return ATMHardwareStatus::kAtmHwSuccess;
}

ATMHardwareStatus SampleATMHardware::eject_cash_deposit() {
  return ATMHardwareStatus::kAtmHwSuccess;
}

ATMHardwareStatus SampleATMHardware::dispense_cash() {
    return ATMHardwareStatus::kAtmHwSuccess;
}

ATMHardwareStatus SampleATMHardware::cancel_cash_dispense() {
  return ATMHardwareStatus::kAtmHwSuccess;
}
