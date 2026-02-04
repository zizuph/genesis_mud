/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

#define TP this_player()

create_food()
{
   set_name("honeycomb");
   add_name("mystic_food");
  add_adj(({"piece of", "golden"}));
   set_long("A piece of honeycomb, fresh from a hive, dripping with honey.\n");
   set_amount(20); /* 50 grams of food. */
   add_prop(OBJ_I_WEIGHT, 300); 
   add_prop(OBJ_I_VOLUME, 100);
}

special_effect(){
   
   object full;
   int old;
   
   
   TP->catch_msg("Amazing! Glory! You feel totally energized!\n");
   TP->add_fatigue(100);
   TP->add_tmp_stat(1, 12, 200);
   TP->heal_hp(5);
   if(random(2)){
      old = TP->query_skill(130005);
      TP->set_skill(130005, old + 1);
   }
}

