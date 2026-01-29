inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
	set_name("platemail");
	add_adj(({"red-stained","adamantine"}));
	set_short("red-stained adamantine platemail");
	set_long("Oooo...scary platemail.\n");
	set_ac(5 + random(2));
	set_am( ({ 0, 0, 0}) );
	set_at(A_TORSO | A_ARMS);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 500 + random(100));
	add_prop(OBJ_I_VOLUME, 300 + random(50));
}
