inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
	set_name("cape");
	add_adj("jet-black");
	set_short("jet-black cape");
	set_long("Scary cape.\n");
	set_ac(5 + random(2));
	set_am( ({ 0, 0, 0}) );
	set_at(A_ROBE);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 300 + random(100));
	add_prop(OBJ_I_VOLUME, 100 + random(50));
}
