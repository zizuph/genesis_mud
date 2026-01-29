inherit "/std/food.c";
#include <stdproperties.h>
#include <macros.h>

void
create_food()
{

	set_name("berries");
	set_pname("berries");
	set_short("purple berries");
	set_pshort("purple berries");
	set_adj("ripe");
	add_adj("delicious");
	set_long("A large bunch of ripe purple wildberries.\n\n");
	set_amount(40);
	add_prop(OBJ_I_WEIGHT, 65);
	add_prop(OBJ_I_VOLUME, 65);
}

