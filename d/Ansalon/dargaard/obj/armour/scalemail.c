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
    set_name("scalemail"); 
    add_name("mail"); 
    add_name(DARGAARD_ARMOUR); 
    set_adj("rusty"); 
    add_adj("black"); 
    set_short("rusty black scalemail"); 
    set_ac(20); 
    set_at(A_BODY); 
    set_am( ({ 3, -10, 3 }) ); 
    set_short("rusty black scalemail"); 
    set_long("This is a rusty scalemail that has been made out of "+ 
             "blackened iron. A few scales have fallen off, making a "+ 
             "fairly large hole in the armour but it still might "+ 
             "provide some protection from various blows.\n");     

    add_prop(OBJ_I_VOLUME, 6050); 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_BODY)); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25)); 
} 
