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
	add_adj("double-bladed");
	add_adj("steel");
	set_short("double-bladed steel axe");
	set_pshort("double-bladed steel axes");
	set_long("This axe has a broad, double-bladed axe head, solidly bound to a stout wooden handle. It looks quite sharp and capable of inflicting pain.\n");
	set_default_weapon(HIT, PEN, W_AXE, W_SLASH | W_BLUDGEON, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
