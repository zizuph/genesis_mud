/* MCLUB - the key to the Gate to the area */
inherit "/std/key";
#include "defs.h"
create_key() {
  set_adj("arcane");
  add_adj("brass");
  set_long("It is a large arcane brass key.\n");
   add_name(MCLUB_GATEKEY);
  set_key(GATE_KEY_NUM);
}
