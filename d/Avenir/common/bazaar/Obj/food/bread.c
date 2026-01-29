inherit "/std/food.c";
#include <stdproperties.h>
#include <macros.h>

void
create_food()
{
	set_name("bread");
	set_short("bread");
	set_long("A large chunk of warm bread torn hastily from a loaf.\n" );

	set_amount(40);
	add_prop(OBJ_I_WEIGHT, 65);
	add_prop(OBJ_I_VOLUME, 65);
}
