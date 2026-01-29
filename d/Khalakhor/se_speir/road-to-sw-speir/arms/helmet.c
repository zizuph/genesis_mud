/*
 * A basic helmet in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"

#include "../defs.h"

inherit KSTDARMOUR;

void
create_khalakhor_armour ()
{
  set_name("helmet");
  add_name(({"mail"}));
  add_adj("steel");
  set_short("steel helmet");
  set_long("This helmet is made of steel plates, with a ring going around "+
           "the head and two wing-like covers over the ears. It looks "+
           "rather mediocre, both quality and weight-wise.\n");
  set_default_armour(20, A_HEAD|A_EARS, ({0,0,0}));
  
}
