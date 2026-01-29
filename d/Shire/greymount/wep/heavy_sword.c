/*
	*Cruddy weapon for the orc race guild npc guard
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
	set_name("sword");
	add_adj("heavy");
	add_adj("steel");
	set_short("heavy steel sword");
	set_pshort("heavy steel swords");
	set_long("This sword is heavy and a bit unwieldy, but could probably still aid in combat.\n");
	set_default_weapon(HIT, PEN, W_SWORD, W_SLASH | W_BLUDGEON, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, 5500 + random(1000));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
