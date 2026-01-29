/*
	*An Axe for the woodsmen of Archet
	*Altrus, June 2005
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
	set_name("axe");
	add_adj("broad-bladed");
	add_adj("steel");
	set_short("broad-bladed steel axe");
	set_pshort("broad-bladed steel axes");
	set_long("This is a steel axe used to chop trees. In the hands of a skilled woodsman, this could probably fell several trees in a day. The blade is broad and sharp.\n");
	set_default_weapon(HIT, PEN, W_AXE, W_SLASH | W_BLUDGEON, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
