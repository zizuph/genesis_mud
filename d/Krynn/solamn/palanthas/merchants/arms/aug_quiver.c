/*
 * Mortis 04.2006
 *
 * Quiver sold by Aug, bowyer of Palanthas.
 *
 */

inherit "/std/container";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h";

create_container()
{
	set_name("quiver");
	set_adj("sable-trimmed");
	add_adj("grey-hide");

	set_short("sable-trimmed grey-hide quiver");
	set_long("A quiver of stiff grey hide trimmed at the top with soft, "
	+ "rich black sable fur, it is capable of holding a bundle of "
	+ "arrows within easy reach over the shoulder.  A small \"A\" has "
	+ "been seared near its bottom edge.\n");

    set_slots(A_BACK);
    set_layers(5);
    set_looseness(20);
	set_keep(1);

	add_prop(CONT_I_WEIGHT,     200 + random(75));
	add_prop(CONT_I_VOLUME,     1200 + random(200));
	add_prop(OBJ_I_VALUE,       100 + random(25));
	add_prop(CONT_I_MAX_WEIGHT, 2500);
	add_prop(CONT_I_MAX_VOLUME, 5000);
	add_prop(CONT_I_RIGID, 0);
	add_prop(CONT_I_REDUCE_WEIGHT, 125);
	add_prop(CONT_I_IS_QUIVER, 1);
}

