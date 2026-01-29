inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
	set_name("robe");
	add_name("dark-robe");
	add_adj("hooded");
	set_short("hooded dark-robe");
	set_pshort("hooded dark-robes");
	set_long("This "+short()+" is long, dark, and rather musty smelling.\n");
	set_ac(15 + random(5));
	set_am( ({ -5, 3, 2}) );
	set_at(A_ROBE);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15) + random(5));
	add_prop(OBJ_I_WEIGHT, 1500 + random(500));
	add_prop(OBJ_I_VOLUME, 300 + random(100));
}
