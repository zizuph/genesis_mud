/*
 * A reproduction of the mystic cowl for the npc Gavriel.
 */
#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour(void)
{
   set_name("hooded-cowl");
   set_adj("once-white");
   add_name("cowl");
   add_name("gavriels_mystic_cowl");
   add_name("hood");
   set_short("once-white cowl");
   set_long("A simple once-white cowl, to be worn with a robe. "
       +"This is a religious garment belonging to a former mystic.\n");
   set_ac(5);
   set_at(A_HEAD);
   set_am(({0, 0, 0}));
   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_VALUE, 500);
}
