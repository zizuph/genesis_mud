/*
	*A club for the orc guards nears the backdoor
	*Altrus, June 2005
*/
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 30
#define PEN 25

void create_weapon()
{
	set_name("club");
	add_adj("massive");
	add_adj("iron");
	set_short("massive iron club");
	set_pshort("massive iron clubs");
	set_long("This brutal looking iron club is long, nearly two and a half feet in length. It's surface above the handle is bumpy and pitted. The handle itself iron, wrapped with severely worn leather.\n");
	set_default_weapon(HIT, PEN, W_CLUB, W_BLUDGEON, W_ANYH);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}
