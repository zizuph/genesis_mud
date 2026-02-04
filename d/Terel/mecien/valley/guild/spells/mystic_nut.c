/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

#define TP this_player()

create_food()
{
   set_name("nut");
   add_name("mystic_nut");
   add_name("mystic_food");
   set_long("A beautiful silvery-white nut encased in a simple shell.\n");
   set_adj("silvery-white");
   set_amount(12); /* 50 grams of food. */
   add_prop(OBJ_I_WEIGHT, 10); 
   add_prop(OBJ_I_VOLUME, 100);
}



special_effect(){
   
   object full;
   int old, intox;
   
   
   TP->catch_msg("It is delicious and sends a spiritual feeling throughout your body.\n");
   TP->add_mana(10);
   if(random(2)){
      old = TP->query_skill(130005);
      TP->set_skill(130005, old + 1);
   }
}

