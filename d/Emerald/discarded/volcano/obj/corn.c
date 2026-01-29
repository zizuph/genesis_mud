inherit "/std/food.c";
#include <stdproperties.h>
#include <macros.h>

void
create_food()
{
	set_name("corn");
	add_name("cob");
	add_name("cob of corn");
	set_short("cob of corn");
	set_adj("fresh");
	add_adj("delicious");
	set_long("A large cob of freshly picked corn on the cob.\n");

	set_amount(50);
	add_prop(OBJ_I_WEIGHT, 65);
	add_prop(OBJ_I_VOLUME, 65);
}
