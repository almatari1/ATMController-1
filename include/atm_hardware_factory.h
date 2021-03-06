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
 * atm_hardware_factory.h
 *
 *  Created on: Mar 4, 2021
 *      Author: ashish
 *
 *  Description: ATM Hardware Factory definition.
 */

#ifndef INCLUDE_ATM_HARDWARE_FACTORY_H_
#define INCLUDE_ATM_HARDWARE_FACTORY_H_

#include "atm_hardware_interface.h"

namespace atmhardwarefactory {

  using atmhardwareinterface::ATMHardwareInterface;

  // class that returns an interface to requested ATM Hardware
  class ATMHardwareFactory {
  public:
    static ATMHardwareInterface* GetATMHardwareInterface(unsigned int hw_id=0);
  };

} // namespace atmhardwarefactory

#endif /* INCLUDE_ATM_HARDWARE_FACTORY_H_ */
