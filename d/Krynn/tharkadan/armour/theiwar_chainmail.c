/* Dwarven chainmail. Larger races cannot wear it. */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
   set_name("chainmail");
   set_ac(35);
   set_at(A_TORSO);
   set_am( ({ -2, 3, 0 }) );
   set_adj("steel");
   set_adj("dwarven");
   set_short("dwarven steel chainmail");
   set_long("This is a suit of fine chainmail of steel in the style " +
       "worn by the dark dwarves of the Theiwar clan.\n");
   add_prop(OBJ_I_VOLUME, 10000);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(35, A_TORSO));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35));

   set_af(TO);

}

mixed
wear(object what)
{
    if(TP->query_race_name() != "dwarf" && TP->query_race() != "gnome" &&
       TP->query_race_name() != "goblin" && TP->query_race() != "hobbit")
	return "The suit of chainmail is designed to fit a dwarf. You " +
           "are too big to wear this armour.\n";

    return 0;
}
