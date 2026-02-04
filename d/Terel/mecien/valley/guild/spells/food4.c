/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

#define TP this_player()

create_food()
{
   set_name("cheese");
   add_name("mystic_food");
   add_adj(({"round of", "soft", "white"}));
   set_long("A round of white soft white cheese.\n");
   set_amount(80); /* 50 grams of food. */
   add_prop(OBJ_I_WEIGHT, 300); 
   add_prop(OBJ_I_VOLUME, 100);
}

special_effect(){
   
   object full;
   int old;
   
   
   TP->catch_msg("Fat and delicious, the cheese melts in your mouth!\n");
   TP->add_tmp_stat(5, 10, 100);
   TP->heal_hp(5);
   if(random(2)){
      old = TP->query_skill(130005);
      TP->set_skill(130005, old + 1);
   }
}

