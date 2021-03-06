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
 * atm_hardware_factory.cc
 *
 *  Created on: Mar 4, 2021
 *      Author: ashish
 *
 *  Description: ATM Hardware Factory implementation.
 */

#include <iostream>
#include "../include/atm_hardware_factory.h"
#include "../include/sample_atm_hardware.h"

namespace atmhardwarefactory {

  // class static method
  ATMHardwareInterface* ATMHardwareFactory::GetATMHardwareInterface(unsigned int hw_id) {

    // can point to any ATM hardware that inherits the ATMHardwareInterface
    ATMHardwareInterface *atm_hw_interface = NULL;

    try {
      // get atm hardware based on id, defaults to SampleATMHardware for now
      atm_hw_interface = new SampleATMHardware();
    }
    catch (std::bad_alloc &ba) {
      std::cerr << "GetATMHardwareInterface: bad_alloc caught: " << ba.what() << "\n";
    }

    return atm_hw_interface;
  }

} // namespace atmhardwarefactory

