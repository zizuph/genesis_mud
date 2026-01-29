/*
 * A spear in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"
#include "../defs.h"

inherit KSTDWEAPON;

void
create_khalakhor_weapon ()
{
  set_name("spear");
  add_adj(({"blackened", "short"}));
  set_short("blackened short spear");
  set_long("This spear is somewhat short, about five feet long, making it "+
           "possible to be wielded in one hand only. The spearhead is "+
           "somewhat wide, blackened and flared for toughness.\n");
  set_default_weapon(25, 25, W_POLEARM, W_IMPALE, W_RIGHT);
}
