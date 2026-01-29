/*
	*An war pick for the dwarven money changer in the 'shaws
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
	set_name("war pick");
	add_name("pick");
	add_adj("rusty");
	add_adj("steel");
	set_short("rusty steel war pick");
	set_pshort("rusty steel war picks");
	set_long("This odd looking weapon is made from piece of steel shaped in a ninety-degree angle, the handle-end round and wrapped in old leather, the business end coming to a point, slight curved. The steel is a bit rusty, due to neglect. It looks quite capable of both smashing someone and poking holes in someone.\n");
	set_default_weapon(HIT, PEN, W_CLUB, W_IMPALE | W_BLUDGEON, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
