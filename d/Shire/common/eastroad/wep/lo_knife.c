inherit "/std/weapon";

#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

create_weapon()
{
	set_name("knife");
	set_pname("knives");
	set_adj("long");
	set_short("long knife");
	set_pshort("long knives");
	set_long(
		"This is a knife with a very long blade. It look "+
		"very sharp, and can cut through most things.\n");
	set_default_weapon(18, 22, W_KNIFE, W_IMPALE, W_ANYH, 0);
	set_pm(({ -1, 0, 1 }));

	add_prop(OBJ_I_WEIGHT, 3000);
	add_prop(OBJ_I_VOLUME, 1200);
	add_prop(OBJ_I_VALUE, 700);
}

