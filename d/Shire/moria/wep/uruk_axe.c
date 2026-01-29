/*
	*An Axe the hulking uruk-hai in Moria
	*Altrus, July 2005
	*
*/
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 35
#define PEN 35

void create_weapon()
{
	set_name("battle-axe");
	add_name("axe");
	add_adj("broad-bladed");
	set_short("broad-bladed battle-axe");
	set_pshort("broad-bladed battle-axes");
	set_long("This appears to be a rather durable axe. There are a few notches in the blade, but otherwise it is quite sharp and lethal-looking.\n");
	set_default_weapon(HIT, PEN, W_AXE, W_SLASH | W_BLUDGEON, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
