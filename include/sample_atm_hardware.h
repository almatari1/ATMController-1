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
 * sample_atm_hardware.h
 *
 *  Created on: Mar 4, 2021
 *      Author: ashish
 *
 *  Description: A Sample ATM Hardware.
 */

#ifndef INCLUDE_SAMPLE_ATM_HARDWARE_H_
#define INCLUDE_SAMPLE_ATM_HARDWARE_H_

#include <string>
#include "atm_hardware_interface.h"

using namespace atmhardwareinterface;
using std::string;

// Sample ATM Hardware Class
class SampleATMHardware: public ATMHardwareInterface {

public:
  SampleATMHardware(){}
  ~SampleATMHardware(){}

  ATMHardwareStatus get_card_number(string &);
  ATMHardwareStatus eject_card();
  ATMHardwareStatus prepare_to_deposit_cash(const long);
  ATMHardwareStatus prepare_to_dispense_cash(const long);
  ATMHardwareStatus deposit_cash();
  ATMHardwareStatus eject_cash_deposit();
  ATMHardwareStatus dispense_cash();
  ATMHardwareStatus cancel_cash_dispense();
};

#endif /* INCLUDE_SAMPLE_ATM_HARDWARE_H_ */
