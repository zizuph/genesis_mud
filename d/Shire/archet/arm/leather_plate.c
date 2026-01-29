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
	set_name("platemail");
	add_adj(({"leather-lined","iron"}));
	set_short("leather-lined iron platemail");
	set_pshort("leather-lined iron platemails");
	set_long("This "+short()+" is not much as far as platemails go. The iron plates are loosely bound and lined with leather, and seem to offer minimal protection.\n");
	
	add_item(({"iron plates", "plates"}), "The iron plates are dented, but not rusty. Apparently, though old and out-dated, this armour has been cared for over the years.\n");
	
	set_ac(40 + random(10));
	set_am( ({ 1, -2, 1}) );
	set_at(A_TORSO);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(2));
	add_prop(OBJ_I_WEIGHT, 4500 + random(500));
	add_prop(OBJ_I_VOLUME, 1000 + random(250));
}
