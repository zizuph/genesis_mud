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
	add_adj("long-handled");
	add_adj("sharp");
	set_short("long-handled sharp axe");
	set_pshort("long-handled sharp axes");
	set_long("This axe has an unusually long handle. It looks like it is made from polished oak and has been taken good care of. Someone obviously cared for this axe. The single-bladed axe-head is very sharp.\n");
	set_default_weapon(HIT, PEN, W_AXE, W_SLASH | W_BLUDGEON, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
