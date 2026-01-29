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
    set_name("braid"); 
    add_name("_WoHS_sacrificial_giant_braid");   
    add_adj("stone giant"); 
    set_short("stone giant braid"); 
    set_ac(1); 
    set_at(A_WAIST); 
 
    set_long("This tightly-braided length of thick black hair has been " +
        "cut from the scalp of a stone giant! It is long enough to be " +
        "tied around the waist.\n"); 
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" })); 
    add_prop(MAGIC_AM_ID_INFO,
      ({"This braid of black hair is imbued with the natural resistances " +
        "stone giants have to earth magic and poison. It confers some of " +
        "this resistance to the wearer.\n",20})); 
    add_prop(OBJ_S_WIZINFO,"This armour is cut from the corpse of a stone " +
        "giant. It offers 20% protection from earth magic and poison.\n");   

    add_prop(OBJ_I_VOLUME, 2050); 
    add_prop(OBJ_I_WEIGHT, 2500); 
    add_prop(OBJ_I_VALUE, 2500); 
    set_wf(TO); 
} 


varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
 
    if (protectee == query_worn())
      {
          if (prop == MAGIC_I_RES_EARTH)
            return ({ 20, 1}); /* additive */
          if (prop == MAGIC_I_RES_POISON)
            return ({ 20, 1}); /* additive */
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
