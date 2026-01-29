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
    set_name("helmet"); 
    add_name("helm"); 
    add_name(DARGAARD_ARMOUR); 
    set_adj("rusty"); 
    add_adj("iron"); 
    set_short("rusty iron helmet"); 
    set_ac(10); 
    set_at(A_HEAD); 
    set_am( ({ 3, -5, 3 }) ); 
    set_short("rusty iron helmet"); 
    set_long("This is a rusty helmet that has been made out of "+ 
             "blackened iron. The insignia of Dargaard Keep has "+ 
             "been etched in the back of the helmet.\n");     

    add_prop(OBJ_I_VOLUME, 3050); 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_HEAD)); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)); 
} 
