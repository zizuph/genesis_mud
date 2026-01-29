/*
	*Hauberk for hulking uruk-hai in Moria
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
	set_name("hauberk");
	add_adj(({"sleeveless","silver"}));
	set_short("sleeveless silver hauberk");
	set_pshort("sleeveless silver hauberks");
	set_long("This "+short()+" is made from interlocking chains of silver links. Although hauberks commonly cover arms as well as the body, this one has no arm protection. It looks like when worn it would hang down to the knees\n");
	
	set_ac(30 + random(10));
	set_am( ({ 1, 2, -3}) );
	set_at(A_TORSO);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 5500 + random(500));
	add_prop(OBJ_I_VOLUME, 2500 + random(250));
}
