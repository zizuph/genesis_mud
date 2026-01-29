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
    set_name("chainmail"); 
    add_name("mail"); 
    add_name(DARGAARD_ARMOUR); 
    set_adj("rusty"); 
    add_adj("black"); 
    set_short("rusty black chainmail"); 
    set_ac(15); 
    set_at(A_BODY); 
    set_am( ({ -10, 3, 3 }) ); 
    set_short("rusty black chainmail"); 
    set_long("This is a rusty chainmail that has been made out of "+ 
             "blackened iron. Half of the chains have fallen off "+ 
             "but it still might provide some protection from various "+ 
             "blows.\n");     

    add_prop(OBJ_I_VOLUME, 6050); 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_BODY)); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)); 
} 
