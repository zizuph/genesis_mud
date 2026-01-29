/*
	*Leather cap for the woodsmen of Archet
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
    set_name("cap");
    add_adj(({"dented","iron"}));
    set_short("dented iron cap");
    set_pshort("dented iron caps");
    set_long("This iron cap barely covers the head. The metal is dented in several places, making for an uncomfortable fit.\n");
    set_ac(20 + random(10));
    set_am( ({ 0, 0, 0}) );
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) - random(2));
    add_prop(OBJ_I_WEIGHT, 100 + random(50));
    add_prop(OBJ_I_VOLUME, 100 + random(20));
}
