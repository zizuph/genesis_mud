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
    set_name("cloak"); 
    add_name(DARGAARD_ARMOUR); 
    set_adj("dirty"); 
    add_adj("black"); 
    set_short("dirty black cloak"); 
    set_ac(5); 
    set_at(A_ROBE); 
    set_am( ({ -2, -2, -2 }) ); 
    set_short("dirty black cloak"); 
    set_long("This is a dirty black cloak that is covered with "+ 
             "mud and dirt. The edges of the cloak has been shredded "+ 
             "and the insignia of Dargaard Keep is barely visible on the "+ 
             "back.\n");     

    add_prop(OBJ_I_VOLUME, 1050); 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(5, A_ROBE)); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5)); 
} 
