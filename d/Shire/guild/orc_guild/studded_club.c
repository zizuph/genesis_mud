/*
	*Cruddy weapon for the orcs outside the orc race guild
	*Altrus, May 2005
*/
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 25
#define PEN 35

void create_weapon()
{
	set_name("club");
	add_adj("metal-studded");
	add_adj("wooden");
	set_short("metal-studded wooden club");
	set_pshort("metal-studded wooden clubs");
	set_long("This club is nothing more than a piece of dense wood with small pieces of sharp metal pounded into the head.\n");
	set_default_weapon(HIT, PEN, W_CLUB, W_SLASH | W_BLUDGEON, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
