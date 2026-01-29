/*
 * WCLOAK.c
 * Wool Cloak, for Vilgurn, npc head of Keepers of Telberin racial guild.
 * - Alaron November 1996
 */

#include "/d/Emerald/defs.h"
#include "../default.h"
#include <wa_types.h>

inherit "/std/armour";

void
create_armour()
{
  set_name("cloak");
  set_adj("wool");
  add_adj("black");

  set_short("black wool cloak");

  set_at(A_ROBE);
  set_ac(8);

  set_long("This is a long, black cloak. It is made of wool and probably provides more "+
	   "comfort and warmth than any real protection.\n");
}
