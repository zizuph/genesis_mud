/*
 * Mortis 02.2006
 * Simple saddlebag for horses.
 */

#include "../../local.h"

inherit "/d/Genesis/std/wearable_pack.c";
inherit "/lib/keep";

void
create_wearable_pack()
{

	set_short("leather saddlebag");
	set_pshort("leather saddlebags");
	set_long("A large, brown leather saddlebag.  It's a little too cumbersome "
	+ "to be used as a personal pack.  It would be best draped on a steed.\n");

	set_name("saddlebag");
	add_name(({"bag"}));
	add_pname(({"saddlebags","bags"}));
	add_adj("leather");

	add_prop(CONT_I_WEIGHT, 1400 + random(150));
	add_prop(CONT_I_VOLUME, 2000 + random(200));
	add_prop(CONT_I_MAX_WEIGHT, 345000);
	add_prop(CONT_I_MAX_VOLUME, 290000);
    add_prop(CONT_I_REDUCE_WEIGHT, 150);

	add_prop(OBJ_I_VALUE, 351 + random(20));

	set_keep(1);
	set_mass_storage(1);
}
