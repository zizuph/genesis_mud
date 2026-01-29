/*
	*A club for the hulking uruk-hai in Moria
	*Altrus, July 2005
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
	set_name("crowsbeak");
	add_name("club");
	add_adj("blackened");
	add_adj("iron");
	set_short("blackened iron crowsbeak");
	set_pshort("blackened iron crowsbeaks");
	set_long("This hammer is made from an iron hammer head rivited to hardened wood handle. The iron head has a sharp spike at the top and a curved spike opposite the flat hammer, hence the name 'crowsbeak'.\n");
	set_default_weapon(HIT, PEN, W_CLUB, W_IMPALE | W_BLUDGEON, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
