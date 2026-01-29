/* c_robes.c is cloned by /telberin/npc/cler_1.c */
 
inherit "/std/armour";
 
#include "default.h"
#include <formulas.h>

void
create_armour()
{
    set_name("robes");
    set_short("clerical robes");
    set_long("These sea green robes are worn by Elven clerics of the " +
             "Goddess of Nature. They are confortable and warm.\n" );
    set_adj("clerical");
 
    set_ac(8);
    set_at(A_ROBE);
    
    add_prop(OBJ_I_WEIGHT, 546);
    add_prop(OBJ_I_VOLUME,  341);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8) + random(10));
}
