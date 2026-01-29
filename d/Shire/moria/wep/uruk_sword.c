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
	set_name("sword");
	add_name("jagged-edged");
	add_adj("bastard");
	set_short("jagged-edged bastard sword");
	set_pshort("jagged-edged bastard swords");
	set_long("This rather vicious looking sword has a " +
             "nasty jagged-edge. It is a bit shorter than " +
             "its cousin, the great-sword, and so not truly " +
             "a two-handed weapon. Its weight feels " +
             "comfortable in your hand.\n");
	set_default_weapon(HIT, PEN, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
