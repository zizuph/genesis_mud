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

#define HIT 15
#define PEN 25

void create_weapon()
{
	set_name("knife");
	add_adj("long");
	add_adj("chipped");
	set_short("long chipped knife");
	set_pshort("long chipped knives");
	set_long("This is an orcish weapon, not very sharp, but adequate enough for stabbing.\n");
	set_default_weapon(HIT, PEN, W_KNIFE, W_SLASH | W_IMPALE, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
