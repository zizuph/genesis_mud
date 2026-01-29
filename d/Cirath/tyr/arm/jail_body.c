/*This is the standard armour for the guards in the jail of Tyr. */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
	set_name("breastplate");
	set_short("arthasian breastplate");
	set_long("This is a standard armour for the guards in the jail of Tyr. "
		+"In the center you can see the a mark that shows you that "
		+"this is a property of the Jail in Tyr. It is of good quality "
		+"even though it comes from a place like a jail. The guards "
		+"will probably have to defend themself from prisoners "
		+"sometime. The breastplate will give you good protection and "
		+"it might even save you life in a real fight.\n");

	set_adj("arthasian");


	set_ac(30);
	set_at(A_BODY);

	add_prop(OBJ_I_WEIGHT, 9500);
	add_prop(OBJ_I_VOLUME, 5000);
}
