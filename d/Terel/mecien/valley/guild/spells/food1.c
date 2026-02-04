/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

#define TP this_player()

create_food()
{
   set_name("cake");
   add_name("mystic_food");
   set_adj("rum");
  set_long("A large piece of sweet rum cake. It smells " +
  "so wonderful, but highly alcoholic!\n");
   set_amount(50); /* 50 grams of food. */
   add_prop(OBJ_I_WEIGHT, 300); 
   add_prop(OBJ_M_NO_GET, "@@check");
   add_prop(OBJ_I_VOLUME, 100);
}


check(){
   if(TP->query_alignment()<0){
      TP->catch_msg("A spirit appears and lances your hand!\n");
      TP->heal_hp(-100);
      return "You draw back your wounded hand.\n";
   }
   if(TP->query_prop("blessed")) return 0;
   
   return "Your hand seems to pass through it.\n";
   
}

special_effect(){
   
   object full;
   int old, intox;
   
   
   TP->catch_msg("It is quite delicious, you feel so wonderful!\n");
   TP->heal_hp(20);
   TP->drink_alco(100);
   if(random(2)){
      old = TP->query_skill(130005);
      TP->set_skill(130005, old + 1);
   }
}

