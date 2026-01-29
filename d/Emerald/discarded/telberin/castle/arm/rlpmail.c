/*
 * RLPMAIL.c
 * Rigid Leather Plate Mail for Vilgurn, npc guildmaster of the Keepers of Telberin
 * - Alaron November 1996
 */

#include "/d/Emerald/defs.h"
#include "../default.h"
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

void
create_armour()
{
  set_name("platemail");
  add_name("mail");
  set_adj("leather");
  add_adj("rigid");
  add_adj("plate");
   add_name("suit");

   set_short("suit of rigid leather platemail");
  set_long("This set of armour is very well made. It is a set of thick, rigid leather "+
	   "plates sewn over a latticework of thick hide and scales from small animals, "+
	   "making the underlying layer seem like chainmail. The suit covers the shoulders "+
	   "and the torso, as well as the waist. This armour probably provides very good "+
	   "protection against most types of attacks.\n");

  set_at(A_TORSO);
  set_ac(39);

  add_prop(OBJ_I_WEIGHT, 8000);
  add_prop(OBJ_I_VOLUME, 6000);

  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(39));
}
