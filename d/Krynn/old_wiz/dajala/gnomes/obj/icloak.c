inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_armour()
{
	set_name("cloak");
	set_adj("dirty");
	add_adj("brown");
	set_short("dirty brown cloak");
	set_long("It is made of brown leather.\n");
	set_default_armour(8, A_ROBE);

	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8));
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(8, A_ROBE));
	add_prop(OBJ_I_VOLUME, 2000);
}
