/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

#define TP this_player()

create_food()
{
   set_name("fish");
   add_name("mystic_food");
   set_adj("smoked");
   set_long("A large smoked fish, ready to be eaten.\n");
   set_amount(200); /* 50 grams of food. */
   add_prop(OBJ_I_WEIGHT, 300); 
   add_prop(OBJ_I_VOLUME, 100);
}

special_effect(){
   
   object full;
   int old;
   
   
   TP->catch_msg("You feel mighty and powerful after consuming the delicious fish!\n");
   TP->add_tmp_stat(2, 50, 100);
   TP->heal_hp(5);
   if(random(2)){
      old = TP->query_skill(130005);
      TP->set_skill(130005, old + 1);
   }
   full->set_duration(120);
}

