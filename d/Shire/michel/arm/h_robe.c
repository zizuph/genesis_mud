/* Standard hobbits equipment coded by Anri */
inherit "/std/armour";
 
#include "/sys/macros.h"
#include <stdproperties.h>
#include <wa_types.h>
#include "/sys/formulas.h"
 
void
create_armour()
{ set_name("robe");
set_short("thick robe");
set_long("This is a thick woven robe crafted from a nice wool. \n"
       + "Some bronze plates give a nice protection to your body. \n"
       + "Though, it is not an armour for the great warrior. \n");
set_adj(({"thick","woven","wool"}));
set_ac(12);
set_at(A_BODY);
set_am(({1,-2,1}));
add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12)-random(10));
add_prop(OBJ_I_VOLUME,100);
add_prop(OBJ_I_WEIGHT,950);
}
 
string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}
 
 
void init_recover(string arg)
{
    init_arm_recover(arg);
}
