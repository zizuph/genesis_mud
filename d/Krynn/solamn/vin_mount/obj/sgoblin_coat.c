/*
 * Coat worn by sneaky goblin guard in cave along road
 * south of Palanthas.
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../local.h"

public void
create_armour()
{
	set_name("coat");
	set_adj("worn");
	add_adj(({"leather"}));
	set_short("worn leather coat");
	set_long("With dark stains on both elbows and around the collar, this "
	+ "leather coat appears in well worn disrepair.  Though once secured "
	+ "with buckle straps up the front, the buckles have rusted and fallen "
	+ "off.  It could still provide slight protection especially from "
	+ "contusions along the arms and body, but its prime days are past.\n");

	set_at(A_BODY | A_ARMS);
	set_ac(14);
	set_am(({0, -2, 2}));
	set_condition(1);
}
