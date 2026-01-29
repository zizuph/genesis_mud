/*
	*A knife for the hulking uruk-hai in Moria
	*Altrus, July 2005
*/
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 25
#define PEN 25

void create_weapon()
{
	set_name("blade");
	add_name("knife");
	add_adj("sleek");
	add_adj("curved");
	set_short("sleek curved blade");
	set_pshort("sleek curved blades");
	set_long("This is a most interesting knife. Its blade is roughly half the length of a human's forearm. The handle curves around back to reconnect with the blade halfway up its length. When wielded, the blade points back at the wielders elbow. As such, it is much more suited for slashing attacks rather than stabbing.\n");
	set_default_weapon(HIT, PEN, W_KNIFE, W_SLASH, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
