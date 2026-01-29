/*
	*An Axe for the orc guards nears the backdoor
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
	set_name("axe");
	add_adj("leather-bound");
	add_adj("steel");
	set_short("leather-bound steel axe");
	set_pshort("leather-bound steel axes");
	set_long("The handle and axe-head both are made from polished steel. The handle is bound with thin leather strips, making for a decent grip. The blade isn't as sharp as it could be, but still sharp enough to be lethal.\n");
	set_default_weapon(HIT, PEN, W_AXE, W_SLASH | W_BLUDGEON, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
