inherit "/std/weapon";

#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 25
#define PEN 9

void create_weapon()
{
	set_name("club");
	add_name("frying pan");
	add_name("pan");
	add_adj("flat");
	add_adj("iron");
	set_short("flat iron frying pan");
	set_pshort("flat iron frying pans");
	set_long("This metal pan has seen better days. From it's many dents you can tell that it has been well used. It looks like it would hurt if you were hit with it.\n");
	set_default_weapon(HIT, PEN, W_CLUB, W_BLUDGEON, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
