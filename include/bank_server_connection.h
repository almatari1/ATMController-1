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
 * bank_server_connection.h
 *
 *  Created on: Mar 4, 2021
 *      Author: ashish
 *
 *  Description: Bank Server Connection Class.
 *               Note: This is only to simulate bank connection functionality.
 */

#ifndef INCLUDE_BANK_SERVER_CONNECTION_H_
#define INCLUDE_BANK_SERVER_CONNECTION_H_

#include <string>
#include "atm_common_defs.h"
#include "bank_api.h"

using namespace bankapi;
using std::string;

// Bank Server Connection class
class BankServerConnection {

public:

  BankServerConnection(){}
  ~BankServerConnection(){}

  BankAPI* ConnectToBank(const string bank_id);
  void DisconnectBank(const BankAPI* bank_ptr);

  string GetBankIDFromCard(const string card_number);
};

#endif /* INCLUDE_BANK_SERVER_CONNECTION_H_ */
