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
    set_name("pelt"); 
    add_name(DARGAARD_ARMOUR); 
    add_name("cloak"); 
    set_adj("hellhound"); 
    add_adj("ash-grey");
    add_adj("ash");
    add_adj("grey"); 
    set_short("ash-grey pelt"); 
    set_ac(19);
    set_at(A_ROBE); 
    set_long("This ash-grey pelt cut from the corpse of a hellhound " +
             "shimmers slightly as you hold it towards the light. A few " +
             "pieces of skin and flesh can still be found on it.\n"); 

    add_prop(OBJ_I_VOLUME, 1050); 
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VALUE,  3000); 
} 

