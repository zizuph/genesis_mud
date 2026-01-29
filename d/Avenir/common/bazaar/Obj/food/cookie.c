inherit "/std/food.c";
#include <stdproperties.h>
#include <macros.h>

void
create_food()
{
	set_name("cookie");
	set_short("large cookie");
	set_long("A large, somewhat stale, but edible cookie.\n");

	set_amount(15);
	add_prop(OBJ_I_WEIGHT, 50);
	add_prop(OBJ_I_VOLUME, 50);
}
