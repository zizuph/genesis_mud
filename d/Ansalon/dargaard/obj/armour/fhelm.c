inherit "/std/armour"; 
inherit "/lib/keep"; 

#include <wa_types.h> 
#include <formulas.h> 
#include <stdproperties.h> 
#include <macros.h> 
#include "/d/Ansalon/common/defs.h" 
#include "../../local.h" 

void 
create_armour() 
{ 
    set_name("helm"); 
    add_name("helmet"); 
    add_name(DARGAARD_ARMOUR); 
    set_adj("rusty"); 
    add_adj("full"); 
    set_short("rusty full helm"); 
    set_ac(15); 
    set_at(A_HEAD); 
    set_am( ({ 3, 3, -5 }) ); 
    set_short("rusty full helm"); 
    set_long("This is a rusty full helm that has been made out of "+ 
             "blackened iron. This heavy helmet covers the entire head "+ 
             "and neck with thick iron plates. The insignia of Dargaard "+ 
             "Keep covers the back of the helmet.\n");     

    add_prop(OBJ_I_VOLUME, 6050); 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_HEAD)); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15)); 
} 
