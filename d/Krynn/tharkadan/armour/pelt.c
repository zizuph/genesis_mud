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
    add_adj("snow-white"); 
    set_short("snow-white pelt"); 
    set_ac(30); 
    set_at(A_ROBE); 
    set_am( ({ -1, 2, -1 }) ); 
    set_long("This snow-white pelt cut from the corpse of a winter wolf " +
             "shimmers slightly as you hold it " + 
             "towards the light. A few pieces of skin and flesh can " + 
             "still be found on it.\n"); 
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" })); 
    add_prop(MAGIC_AM_ID_INFO,
      ({"This pelt has been cut from the corpse of a winter wolf, an " +
        "evil arctic-dwelling beast. Some of the creatures " +
        "natural protection to cold will be transferred to the wearer " +
        "of this cloak.\n",20})); 
    add_prop(OBJ_S_WIZINFO,"This armour comes from the pelt of a " +
             "winter wolf. It offers good protection, and 25% " +
             "additional protection from cold.\n");   

    add_prop(OBJ_I_VOLUME, 1050); 
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VALUE, 2500); 
    set_wf(TO); 
} 


varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
 
    if (protectee == query_worn())
      {
          if (prop == MAGIC_I_RES_COLD)
            return ({ 25, 1}); /* additive */
      }
    else
      return ::query_magic_protection(prop, protectee);
}
 

mixed 
wear(object what) 
{ 
    TP->add_magic_effect(TO);
    return 0; 
} 


mixed 
remove(object what) 
{ 
    wearer->remove_magic_effect(TO); 
    return 0; 
} 
