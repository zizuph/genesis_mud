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
    add_adj("flaming-red"); 
    set_short("flaming-red pelt"); 
    set_ac(30); 
    set_at(A_ROBE); 
    set_am( ({ -1, 2, -1 }) ); 
    set_long("This flaming-red pelt cut from the corpse of a hellhound "+
             "shimmers slightly as you hold it "+ 
             "towards the light. A few pieces of skin and flesh can "+ 
             "still be found on it.\n"); 
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" })); 
    add_prop(MAGIC_AM_ID_INFO,
      ({"This pelt has been cut from the corpse of a hellhound, a beast " +
        "spawned in the fiery wastelands of the Abyss. Some of the creatures " +
        "natural protection to fire will be transferred to the wearer of this "+
        "cloak.\n",20})); 
    add_prop(OBJ_S_WIZINFO,"This armour comes from the pelt of a "+
             "hellhound. It offers good protection, and 25% additional " +
             "protection from fire.\n");   

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
          if (prop == MAGIC_I_RES_FIRE)
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
