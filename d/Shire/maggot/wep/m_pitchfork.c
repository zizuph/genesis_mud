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
	add_name("pitchfork");
	add_adj("three-pronged");
	set_short("three-pronged pitchfork");
	set_pshort("three-pronged pitchforks");
	set_long("This pitchfork has three sharp spikes. It is made for tossing hay, but could cause some damage in a fight.\n");
	set_default_weapon(HIT, PEN, W_POLEARM, W_IMPALE | W_BLUDGEON, W_BOTH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
