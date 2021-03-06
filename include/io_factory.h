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
 * io_factory.h
 *
 *  Created on: Mar 5, 2021
 *      Author: ashish
 *
 *  Description: An factory class that provides provides IO interfaces to
 *                different types of IOs.
 */

#ifndef INCLUDE_IO_FACTORY_H_
#define INCLUDE_IO_FACTORY_H_

#include "io_interface.h"

namespace iofactory {

  using iointerface::IOInterface;

  // class that returns an interface to requested IO
  class IOFactory {
  public:
    static IOInterface* GetIOInterface(unsigned int io_id=0);
  };

} // namespace iofactory

#endif /* INCLUDE_IO_FACTORY_H_ */
