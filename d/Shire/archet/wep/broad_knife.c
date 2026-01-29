/*
	*A hunting knife for the woodsmen of Archet
	*Altrus, June 2005
*/
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 30
#define PEN 35

void create_weapon()
{
	set_name("knife");
	add_adj("broad-bladed");
	add_adj("hunting");
	set_short("broad-bladed hunting knife");
	set_pshort("broad-bladed hunting knives");
	set_long("This would be the perfect knife for a huntsman. Its sharpened blade is perfect for skinning. It would probably serve in a pinch, if one were to use it in a fight.\n");
	set_default_weapon(HIT, PEN, W_KNIFE, W_SLASH | W_IMPALE, W_LEFT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
