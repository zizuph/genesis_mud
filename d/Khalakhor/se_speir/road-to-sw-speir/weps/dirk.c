/*
 * A dirk in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"
#include "../defs.h"

inherit KSTDWEAPON;

void
create_khalakhor_weapon ()
{
  set_name("dirk");
  add_name(({"knife", "dagger"}));
  add_adj(({"steel-bladed", "bone-hilted"}));
  set_short("steel-bladed bone-hilted dirk");
  set_long("This dirk has a long blade forged out of steel and a hilt made "+
           "out of bone. It doesn't seem to be an extremely efficient "+
           "weapon, but is probably used as an auxiliary one, or as a "+
           "utility.\n");
  set_default_weapon(15, 15, W_KNIFE, W_IMPALE, W_ANYH);
}
