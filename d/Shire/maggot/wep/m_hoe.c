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
	set_name("polearm");
	add_name("hoe");
	add_adj("flat-bladed");
	set_short("flat-bladed hoe");
	set_pshort("flat-bladed hoes");
	set_long("This hoe has a broad, flat metal blade used for turning soil. It might hurt if used as a weapon.\n");
	set_default_weapon(HIT, PEN, W_POLEARM, W_IMPALE | W_BLUDGEON, W_BOTH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
