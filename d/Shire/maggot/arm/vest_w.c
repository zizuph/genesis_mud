inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
	set_name("vest");
	add_adj(({"worn","leather"}));
	set_short("worn leather vest");
	set_pshort("worn leather vests");
	set_long("This "+short()+" has seen a lot of work, but looks like it will last for a long time to come.\n");
	set_ac(15 + random(5));
	set_am( ({ -5, 3, 2}) );
	set_at(A_ROBE);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15) + random(5));
	add_prop(OBJ_I_WEIGHT, 1500 + random(500));
	add_prop(OBJ_I_VOLUME, 300 + random(100));
}
