/*
	*Cleaver for hacking meat
	*Altrus, May 2005
*/
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 25
#define PEN 30

void create_weapon()
{
	set_name("cleaver");
	add_name("knife");
	add_adj("chipped");
	add_adj("bloody");
	set_short("chipped bloody cleaver");
	set_pshort("chipped bloody cleavers");
	set_long("This cleaver, though chipped, is sharp enough to cut through meat, or at least to hack it to bits.\n");
	set_default_weapon(HIT, PEN, W_KNIFE, W_SLASH | W_BLUDGEON, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
