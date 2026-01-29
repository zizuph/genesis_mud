inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
	set_name("knife");
	set_pname("knives");
	set_adj("sharp");
	set_short("sharp knife");
	set_pshort("sharp knives");
	set_long(
		"A newly forged knife. Or more like a short sword. "+
		"To hobbits it is more a short sword, but it is a knife "+
		"for all others. It is extremly sharp, and it look like it "+
		"could do alot of damage for a skilled user.\n");
	set_default_weapon(19, 20, W_KNIFE, W_IMPALE, W_ANYH, 0);
	set_pm(({ -2, 0, 2 }));
	add_prop(OBJ_I_WEIGHT, 2000);
	add_prop(OBJ_I_VOLUME, 1500);
	add_prop(OBJ_I_VALUE, 1200);
}














