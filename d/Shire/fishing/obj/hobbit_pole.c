/*
	*Fishing pole
	*Altrus, June 2005
*/
inherit "/std/weapon";

#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 5
#define PEN 10

void create_weapon()
{
	set_name("pole");
	add_name("polearm");
	add_adj("wooden");
	add_adj("fishing");
	set_short("wooden fishing pole");
	set_pshort("wooden fishing poles");
	set_long("This looks like it might be used to catch fish.\n");
	set_default_weapon(HIT, PEN, W_POLEARM, W_IMPALE | W_BLUDGEON, W_BOTH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
