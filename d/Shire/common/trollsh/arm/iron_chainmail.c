/*
	*Cruddy armour
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
	add_adj(({"heavy","iron"}));
	set_short("heavy iron chainmail");
	set_pshort("heavy iron chainmails");
	set_long("This "+short()+" seems very old. Rust has started to take purchase on many of the chain links in the armour.\n");
	
	set_ac(30 + random(10));
	set_am( ({ 2, -1, -1}) );
	set_at(A_TORSO);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 7500 + random(500));
	add_prop(OBJ_I_VOLUME, 1000 + random(250));
}
