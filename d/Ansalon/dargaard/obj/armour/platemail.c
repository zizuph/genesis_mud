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
    set_name("breastplate"); 
    add_name("mail"); 
    add_name(DARGAARD_ARMOUR); 
    set_adj("rusty"); 
    add_adj("black"); 
    set_short("rusty black breastplate"); 
    set_ac(25); 
    set_at(A_BODY); 
    set_am( ({ 3, 3, -10 }) ); 
    set_long("This is a rusty breastplate that has been made out of "+ 
             "blackened iron. The heavy plates is attached to both "+ 
             "the back and front of the armour, however big rust "+ 
             "stains cover some of the plates. Judging by the special "+ 
             "forging that has been used to construct this armour, you "+ 
             "realize that it must originate before the cataclysm.\n");     

    add_prop(OBJ_I_VOLUME, 6050); 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_BODY)); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30)); 
} 
