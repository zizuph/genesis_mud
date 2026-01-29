/*
 * Key to Refnas's office
 * Tapakah, 06/2021
 */

#pragma strict_types

#include "defs.h"

inherit "/std/key";

void
create_key()
{
  set_adj("small");
  add_adj("curved");
  set_long("It's a small key that resembles a leech.\n");
  set_key(REFNAS_KEY_ID);
  add_name("_refnas_key");
}
