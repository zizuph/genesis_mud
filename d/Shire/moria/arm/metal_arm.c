/*
	*Iron bracers for the woodsmen of Archet
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
    set_name("bracers");
    add_adj(({"heavy","iron"}));
    set_short("heavy iron bracers");
    set_pshort("heavy iron bracers");
    set_long("These "+short()+" certainly are just that, heavy! They are made from iron, lined with leather. They don't look very comfortable, but might protect you well enough.\n");
    
    set_ac(35);
    set_am( ({ 0, 2, -2}) );
    set_at(A_ARMS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) - random(5));
    add_prop(OBJ_I_WEIGHT, 3500 + random(500));
    add_prop(OBJ_I_VOLUME, 750 + random(100));
}
