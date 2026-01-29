/*
	*Chainmail for hulking uruk-hai in Moria
	*Altrus, July 2005
*/
inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
	set_name("chainmail");
	add_adj(({"heavy","steel"}));
	set_short("heavy steel chainmail");
	set_pshort("heavy steel chainmails");
	set_long("This "+short()+" offers the wearer protection not only of the body, but of the arms as well. It is made from steel rings linked together, forming a decent cover to protect the wearer from the usual cuts and slashes obtained in battle.\n");
	
	set_ac(30 + random(10));
	set_am( ({ 1, 2, -3}) );
	set_at(A_TORSO);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 6500 + random(500));
	add_prop(OBJ_I_VOLUME, 2500 + random(250));
}
