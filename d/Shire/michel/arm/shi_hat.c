/* Standard hobbits equipment coded by Anri */
inherit "/std/armour";
 
#include "/sys/macros.h"
#include <stdproperties.h>
#include <wa_types.h>
#include "/sys/formulas.h"
 
void
create_armour()
{ set_name("hat");
set_short("plumed leather hat");
set_long("This is a nice hobbits hat made of soft leather. \n"
       + "It is decorated with a couloured plume.\n"
       + "All shirriffes and hobbit guards are wearing them. \n");
set_adj(({"nice","plumed","leather"}));
set_ac(6);
set_at(A_HEAD);
set_am(({0,-1,1}));
add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(6)+10);
add_prop(OBJ_I_VOLUME,90);
add_prop(OBJ_I_WEIGHT,390);
}
 
string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}
 
 
void init_recover(string arg)
{
    init_arm_recover(arg);
}
