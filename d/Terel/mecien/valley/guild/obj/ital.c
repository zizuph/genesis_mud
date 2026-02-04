inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

create_armour(){
   set_name("talisman");
   set_adj("ivory");
  set_at(A_MAGIC);
   set_ac(15);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 5);
   add_prop("mystic_armour", 1);
   
   
}

int *
query_shield_slots(){
   return ({ A_BODY, A_LEGS, A_ARMS });
}


