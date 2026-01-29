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
    set_name("hood"); 
    add_name(DARGAARD_ARMOUR); 
    set_adj("rusty"); 
    add_adj("chainmail"); 
    set_short("rusty chainmail hood"); 
    set_ac(5); 
    set_at(A_HEAD); 
    set_am( ({ -5, 3, 3 }) ); 
    set_short("rusty chainmail hood"); 
    set_long("This is a rusty chainmail hood that has been made out of "+ 
             "blackened iron. Half of the chains have fallen off "+ 
             "but it still might provide some protection from various "+ 
             "blows.\n");     

    add_prop(OBJ_I_VOLUME, 3050); 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_HEAD)); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)); 
}
