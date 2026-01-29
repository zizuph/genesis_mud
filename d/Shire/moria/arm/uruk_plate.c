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
	set_name("platemail");
	add_adj(({"dark","steel"}));
	set_short("dark steel platemail");
	set_pshort("dark steel platemails");
	set_long("This "+short()+" is quite bulky. It is heavy and lined with leather, and held in place with leather straps. Although it is heavy and somewhat ungainly looking, it has a decent range of motion.\n");
	
	set_ac(30 + random(10));
	set_am( ({ -3, 1, 2}) );
	set_at(A_TORSO);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 8500 + random(500));
	add_prop(OBJ_I_VOLUME, 2500 + random(250));
}
