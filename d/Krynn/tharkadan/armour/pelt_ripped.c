inherit "/std/armour"; 
inherit "/lib/keep"; 

#include <wa_types.h> 
#include <formulas.h> 
#include <stdproperties.h> 
#include <macros.h> 
#include "/d/Krynn/common/defs.h" 
#include "../local.h" 

void 
create_armour() 
{ 
    set_name("pelt");  
    add_name("cloak"); 
    add_adj("ripped"); 
    set_short("ripped pelt"); 
    set_ac(19);
    set_at(A_ROBE); 
    set_long("This ripped pelt cut from the corpse of a winter wolf, " +
             "while tattered, makes for a handy thick cloak. A few " +
             "pieces of skin and flesh can still be found on it.\n"); 

    add_prop(OBJ_I_VOLUME, 1050); 
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VALUE,  3000); 
} 

