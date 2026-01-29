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

#define HIT 30
#define PEN 30

void create_weapon()
{
	set_name("axe");
	add_adj("sleek");
	add_adj("steel");
	set_short("sleek steel axe");
	set_pshort("sleek steel axes");
	set_long("The handle and axe-head both are made from polished steel. The handle is bound with thin leather strips, making for a good grip. The blade is sharpened and oiled. It looks almost as useful in a fight as it is for chopping trees.\n");
	set_default_weapon(HIT, PEN, W_AXE, W_SLASH | W_BLUDGEON, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
