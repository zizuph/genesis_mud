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
    set_name("rag"); 
    add_name(DARGAARD_ARMOUR); 
    add_name("cloak"); 
    set_adj("dirty"); 
    set_short("dirty rag"); 
    set_ac(1); 
    set_at(A_ROBE); 
    set_am( ({ 1, -2, -1 }) ); 
    set_long("This is the dirty remains of an old cloak.\n");     

    add_prop(OBJ_I_VOLUME, 1050); 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE)); 
    add_prop(OBJ_I_VALUE, 0); 
}

