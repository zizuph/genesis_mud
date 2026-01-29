/*
	*Cruddy armour for the orcs outside the orc race guild
	*Altrus, May 2005
*/
inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
	set_name("shirt");
	add_adj(({"hardened","leather"}));
	set_short("hardened leather shirt");
	set_pshort("hardened leather shirts");
	set_long("This "+short()+" doesn't look like it offers much protection. It looks like the previous owner did nothing to preserve its condition.\n");
	
	set_ac(30 + random(10));
	set_am( ({ -2, 2, 0}) );
	set_at(A_TORSO);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 2500 + random(500));
	add_prop(OBJ_I_VOLUME, 1000 + random(250));
}
