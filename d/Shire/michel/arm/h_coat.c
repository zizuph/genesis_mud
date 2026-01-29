/* Standard hobbits equipment coded by Anri */
inherit "/std/armour";
 
#include "/sys/macros.h"
#include <stdproperties.h>
#include <wa_types.h>
#include "/sys/formulas.h"
 
void
create_armour()
{ set_name("coat");
set_short("small coat");
set_long("This is a small leather coat - a typical hobbitish material. \n"
       + "It is dark green and good for hiding in fields. \n"
       + "You see a small inscription on it : crafted by Lothelia. \n");
set_adj(({"small","leather","hobbits"}));
set_ac(5);
set_at(A_BODY);
set_am(({1,-1,0}));
add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5));
add_prop(OBJ_I_VOLUME,100);
add_prop(OBJ_I_WEIGHT,550);
}
 
string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}
 
 
void init_recover(string arg)
{
    init_arm_recover(arg);
}
