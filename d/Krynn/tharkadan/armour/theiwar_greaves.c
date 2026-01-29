/* Dwarven greaves. Larger races cannot wear it. */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
   set_name("greaves");
   set_ac(32);
   set_at(A_LEGS);
   set_am( ({ -2, 5, 0 }) );
   set_adj("steel");
   set_adj("dwarven");
   set_short("pair of dwarven steel greaves");
   set_pshort("pairs of dwarven steel greaves");
   set_long("A pair of finely crafted greaves of steel in the style " +
       "worn by the dark dwarves of the Theiwar clan.\n");
   add_prop(OBJ_I_VOLUME, 1450);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(32, A_LEGS));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(32));

   set_af(TO);

}

mixed
wear(object what)
{
    if(TP->query_race_name() != "dwarf" && TP->query_race() != "gnome" &&
       TP->query_race_name() != "goblin" && TP->query_race() != "hobbit")
	return "These greaves are designed to fit a dwarf. You are too " +
           "big to wear this armour.\n";

    return 0;
}
