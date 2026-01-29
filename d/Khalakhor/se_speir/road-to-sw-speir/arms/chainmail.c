/*
 * A basic chainmail in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"

#include "../defs.h"

inherit KSTDARMOUR;

void
create_khalakhor_armour ()
{
  set_name("chainmail");
  add_name(({"mail"}));
  add_adj("steel");
  set_short("steel chainmail");
  set_long("This chainmail, sturdy and well-crafted, should provide a "+
           "decent defense for its wearer. The links have been "+
           "thorougly hammered out and feel relatively light.\n");
  set_default_armour(25, A_BODY, ({1,1,-2}));
  
}
