/*
 * A sword in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"
#include "../defs.h"

inherit KSTDWEAPON;

void
create_khalakhor_weapon ()
{
  set_name("backsword");
  add_name(({"sword"}));
  add_adj(({"steel", "narrow"}));
  set_short("steel narrow backsword");
  set_long("This sword only has one sharp edge, as well as the tip sharpened "+
           "for thrust. It also features a knuckle guard and a leather-bound "+
           "grip. It's a weapon which is relatively easy to make and to use "+
           "which made it a favorite among the Port Macdunn's soldiers.\n");
  set_default_weapon(25, 25, W_SWORD, W_SLASH|W_IMPALE, W_RIGHT);
}
