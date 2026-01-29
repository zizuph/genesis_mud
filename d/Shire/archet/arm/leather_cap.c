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
    add_adj(({"thick","leather"}));
    set_short("thick leather cap");
    set_pshort("thick leather caps");
    set_long("This cap barely covers the head. It is made of thick leather, and probably wouldn't do much except turn the occasional blow.\n");
    set_ac(20 + random(10));
    set_am( ({ 0, 0, 0}) );
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) - random(2));
    add_prop(OBJ_I_WEIGHT, 100 + random(50));
    add_prop(OBJ_I_VOLUME, 100 + random(20));
}
