/*
	*Leather tunic for Archet woodsmen
	*Altrus, June 2005
*/
inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
	set_name("tunic");
	add_adj(({"hardened","leather"}));
	set_short("hardened leather tunic");
	set_pshort("hardened leather tunics");
	set_long("This "+short()+" would probably help keep out the elements. It looks next to worthless for protection in a fight though. It is flimsy and old.\n");
	
	set_ac(30 + random(10));
	set_am( ({ -2, 2, 0}) );
	set_at(A_TORSO);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 2500 + random(500));
	add_prop(OBJ_I_VOLUME, 1000 + random(250));
}
