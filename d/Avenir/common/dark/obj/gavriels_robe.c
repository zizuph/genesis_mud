/*
 * Reproduction of the mystic robe for Gavriel the Mystic Cantor
 */
#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour(void)
{
   set_name("robe");
   set_adj("once-white");
   add_name("gavriels_mystic_robe");
   set_short("once-white robe");
   set_long("A simple robe, once white but now gray with "
       +"dirt. A religious garment belonging to a former"
	   +"mystic.\n");
   set_ac(10);
   set_at(A_ROBE);
   set_am(({0, 0, 0}));
   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_VALUE, 500);
    set_default_armour(10, A_ROBE, ({ -2, 0, 2}), 0);
}
