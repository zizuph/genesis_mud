/* Standard hobbits equipment coded by Anri */
inherit "/std/armour";
 
#include "/sys/macros.h"
#include <stdproperties.h>
#include <wa_types.h>
#include "/sys/formulas.h"
 
void
create_armour()
{ set_name("cap");
set_short("green cap");
set_long("This cap is typical for rural hobbits of Michel Delving. \n"
       + "It is small,green and protects your head from the Sun. \n");
set_adj(({"small","green","hobbits"}));
set_ac(5);
set_at(A_HEAD);
set_am(({1,-1,0}));
add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5));
add_prop(OBJ_I_VOLUME,95);
add_prop(OBJ_I_WEIGHT,250);
}
 
string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}
 
 
void init_recover(string arg)
{
    init_arm_recover(arg);
}
