/* Dwarven leather. Larger races cannot wear it. */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
   set_name("armour");
   set_ac(19);
   set_at(A_TORSO);
   set_am( ({ 2, 0, -2 }) );
   set_adj("leather");
   set_adj("grey-green");
   set_short("grey-green leather armour");
   set_long("This is suit of leather armour crafted out of the skin of " +
       "a giant subterranean lizard. It offers reasonable protection " +
       "to the wearer without being too much of a burden.\n");
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(19, A_TORSO));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(19));

   set_af(TO);

}

mixed
wear(object what)
{
    if(TP->query_race_name() != "dwarf" && TP->query_race() != "gnome" &&
       TP->query_race_name() != "goblin" && TP->query_race() != "hobbit")
	return "The suit of leather armour is designed to fit a dwarf. " +
           "You are too big to wear this armour.\n";

    return 0;
}
