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
 * io_factory.cc
 *
 *  Created on: Mar 5, 2021
 *      Author: ashish
 *
 *  Description: IO factory class implementation.
 */

#include <iostream>
#include "../include/io_factory.h"
#include "../include/console_io.h"

namespace iofactory {

  // class static method
  IOInterface* IOFactory::GetIOInterface(unsigned int io_id) {

    // this can point to any IO that inherits the IOInterface
    IOInterface *io_interface = NULL;

    try {
      // get IO based on id, defaults to ConsoleIO
      io_interface = new ConsoleIO();
    }
    catch (std::bad_alloc &ba) {
      std::cerr << "GetIOInterface: bad_alloc caught: " << ba.what() << "\n";
    }

    return io_interface;
  }

} // namespace iofactory
