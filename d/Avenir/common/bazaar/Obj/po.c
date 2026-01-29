inherit "/std/food.c";
#include <stdproperties.h>
#include <macros.h>

void
create_food()
{
	set_name("porridge");
	add_name("porridge");
	add_name("bowl");
	set_short("bowl of porridge");
	set_long("A bowl of luke warm, brownish porridge.\n");

	set_amount(30);
	add_prop(OBJ_I_WEIGHT, 300);
	add_prop(OBJ_I_VOLUME, 300);
}
