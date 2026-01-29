/*
	*A short knife for the woodsmen of Archet
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
	set_name("knife");
	add_adj("short");
	add_adj("wooden-handled");
	set_short("short wooden-handled knife");
	set_pshort("shor wooden-handled knives");
	set_long("This small knife looks like it might be used for anything. It is quite a versatile looking implement. Its blade is sharp, but short.\n");
	set_default_weapon(HIT, PEN, W_KNIFE, W_SLASH | W_IMPALE, W_LEFT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
