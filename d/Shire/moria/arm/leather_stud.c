/*
	*Studded leather armour for the woodsmen of Archet
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
	set_name("armour");
	add_adj(({"leather","metal-studded"}));
	set_short("metal-studded leather armour");
	set_pshort("metal-studded leather armours");
	set_long("This "+short()+" looks as if it has seen better days, but is still in passable condition. Small metal studs adorn the chest piece of the armour.\n");
	
	add_item(({"studs", "piece", "chest piece", "metal studs"}), "The chest piece of the armour is checkerd with small iron studs that come to a rounded point.\n");
	
	set_ac(30 + random(10));
	set_am( ({ -3, 2, 1}) );
	set_at(A_TORSO);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 4500 + random(500));
	add_prop(OBJ_I_VOLUME, 1000 + random(250));
}
