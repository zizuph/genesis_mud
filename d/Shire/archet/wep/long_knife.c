/*
	*A long blade for the woodsmen of Archet
	*Altrus, June 2005
*/
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 30
#define PEN 30

void create_weapon()
{
	set_name("blade");
	add_name("knife");
	add_adj("long");
	add_adj("steel");
	set_short("long steel blade");
	set_pshort("long steel blades");
	set_long("This is a long, sharp blade, perfect for skinning.\n");
	set_default_weapon(HIT, PEN, W_KNIFE, W_SLASH | W_IMPALE, W_LEFT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
