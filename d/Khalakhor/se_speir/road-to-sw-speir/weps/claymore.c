/*
 * A sword in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"
#include "stdproperties.h"
#include "../defs.h"

inherit KSTDWEAPON;

void
create_khalakhor_weapon ()
{
  set_name("claymore");
  add_name(({"sword"}));
  add_adj(({"wide-hilted", "heavy"}));
  set_short("wide-hilted heavy claymore");
  set_long("This claymore is an excellent example of the craftsmanship of "+
           "the bladesmiths of Port Macdunn. Despite being somewhat on the "+
           "heavy side, the sword is perfectly balanced with the wide hilt "+
           "allowing for an excellent grip.\n");
  set_default_weapon(35, 35, W_SWORD, W_SLASH|W_IMPALE, W_BOTH);
  add_prop(OBJ_I_WEIGHT, 4000);
}
