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
	set_name("scimitar");
	add_name("sword");
	add_adj("rusty");
	add_adj("steel-bladed");
	set_short("rusty steel-bladed scimitar");
	set_pshort("rusty steel-bladed scimitars");
	set_long("This scimitar's blade is rusty. Obviously it hasn't been taken care of over the years, however, it would still do some damage if swung hard enough.\n");
	set_default_weapon(HIT, PEN, W_SWORD, W_SLASH | W_BLUDGEON, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
