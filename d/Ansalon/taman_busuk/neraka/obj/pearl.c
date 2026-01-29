inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
	set_name("pearl");
	set_adj("small");
	add_adj("shiny");

	set_long("The pearl is well polished and perfectly round. " +
		"It is probably quite valuable.\n");

	add_prop(OBJ_I_WEIGHT, 15);
	add_prop(OBJ_I_VOLUME, 5);
	add_prop(OBJ_I_VALUE, 500);
}
