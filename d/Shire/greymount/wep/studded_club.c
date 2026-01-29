/*
	*Cruddy weapon for the orcs outside the orc race guild
	*Altrus, May 2005
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
	set_name("club");
	add_adj("studded");
	add_adj("oaken");
	set_short("studded oaken club");
	set_pshort("studded oaken clubs");
	set_long("This club does not appear to be of very good quality. It's is made of an old wood, probably oak, but is worn and cracked extensively. Small iron studs have been driven into the business end of the weapon.\n");
	set_default_weapon(HIT, PEN, W_CLUB, W_BLUDGEON, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
