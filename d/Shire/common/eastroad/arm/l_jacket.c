inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Shire/common/defs.h"

create_armour()
{
	set_name("jacket");
	set_pname("jackets");
	set_adj("leather");
	add_adj("good");
	set_short("leather jacket");
	set_pshort("leather jackets");
	set_long(
		"This is a good and warm leather jacket. It has some fur that covers "+
		"your neck, so you dont get a cold, and at the same time it is hard "+
		"to penetrate with a knife. The leather is ornamented with some decorations "+
		"and appears to be well used.\n");
	set_ac(10);
	set_at(A_BODY);
	set_shield_slot(A_BODY | A_L_ARM | A_R_ARM | A_NECK);
	set_am(({ -2, -1, 3}));
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_BODY) - random(50));
	add_prop(OBJ_I_VOLUME, 2500);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
}

