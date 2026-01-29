/*This is the standard armour for the guards in the jail of Tyr. */

inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
        ::create_armour();
	set_name("breastplate");
	set_short("athasian breastplate");
	set_long("This is a standard armour for the guards in the jail of Tyr. "
		+"In the center you can see the mark that shows you that "
		+"this is property of the Jail in Tyr. It is of good quality "
		+"even though it comes from a place like a jail. The guards "
		+"will probably have to defend themself from prisoners "
		+"sometime. The breastplate will give you good protection and "
		+"it might even save you life in a real fight.\n");

	set_adj("athasian");


	set_ac(30);
        set_am(({1,1,-2}));
	set_at(A_BODY);

	add_prop(OBJ_I_WEIGHT, 9500);
	add_prop(OBJ_I_VOLUME, 5000);
}
