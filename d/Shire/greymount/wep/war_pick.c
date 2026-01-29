/*
	*An war pick for the orc guards nears the backdoor
	*Altrus, June 2005
*/
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 35
#define PEN 35

void create_weapon()
{
	set_name("war pick");
	add_name("pick");
	add_adj("sharpened");
	add_adj("steel");
	set_short("sharpened steel war pick");
	set_pshort("sharpened steel war picks");
	set_long("This cruel looking pick is made of a blackened steel. It is a club of sorts, long handled, but with a sharpened point that extends a foot perpendicular to the shaft. There is much wear about the weapon, but it appears well cared for.\n");
	set_default_weapon(HIT, PEN, W_CLUB, W_IMPALE | W_BLUDGEON, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
