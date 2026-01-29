inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Shire/common/defs.h"

create_armour()
{
	set_name("pants");
	set_adj("pair");
	add_adj("warm");
	set_short("pair of warm pants");
	set_pshort("pairs of warm pants");
	set_long(
		"It's a pair of warm, thick pants. They look well used and "+
		"is inserted with leather on it's back, to sit better when "+
		"wearing it.\n");
	add_prop(OBJ_I_WEIGHT, 1200);
	add_prop(OBJ_I_VOLUME, 5000);
	add_prop(OBJ_I_VALUE, 120);
	set_ac(12);
	set_at(A_LEGS);
	set_af(({ -2, -1, 2 }));
}
