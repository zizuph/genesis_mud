/*
 * A peanut
 */
 
inherit "/std/food";

#include <stdproperties.h>
 
create_food()
{
	set_amount(5);
	set_name("peanut");
	set_short("peanut");
	set_long("It's one of the famous peanuts of Spain.\n");
	add_prop(OBJ_I_VOLUME, 25);
}
