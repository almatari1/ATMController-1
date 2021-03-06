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
 * bank_server_connection.cc
 *
 *  Created on: Mar 4, 2021
 *      Author: ashish
 *
 *  Description: Bank Server Connection implementation.
 *               Note: This is only to simulate bank connection functionality.
 */

#include <iostream>
#include "../include/atm_common_defs.h"
#include "../include/sample_bank.h"
#include "../include/bank_server_connection.h"

using namespace atmcommondefs;

// returns a bank object based on bank id
BankAPI* BankServerConnection::ConnectToBank(const string bank_id) {

  // this can point to any bank object that inherits the BankAPI
  BankAPI *bank_ptr = NULL;

  try {
    // get bank based on bank id, defaults to SampleBank for now
    bank_ptr = new SampleBank();
  }
  catch (std::bad_alloc &ba) {
    std::cerr << "bad_alloc caught: " << ba.what() << "\n";
  }

  return bank_ptr;
}

void BankServerConnection::DisconnectBank(const BankAPI* bank_ptr) {
  // do any disconnection bookkeeping/formalities
}

string BankServerConnection::GetBankIDFromCard(const string card_number) {
  return kDefaultBankId;
}
