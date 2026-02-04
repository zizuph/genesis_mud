/* Creative rights reserved to Mecien(Jeff Babcock) and team. */

inherit "/std/food";
#include <stdproperties.h>

#define TP this_player()

create_food()
{
   set_name("honey");
   add_name("mystic_food");
   add_name("pot");
   add_name("earthen pot");
   add_name("spiced honey");
   set_adj("small earthen pot of");
   set_long("A small earthen pot. It is filled with a smooth " +
      "and rich golden honey, secretly blended with special herbs and spices.\n");
   set_amount(50); /* 50 grams of food. */
   add_prop(OBJ_I_WEIGHT, 300); 
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_VALUE, 3500);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
}


special_effect(){
   
   object full;
   int old, intox;
   
   
   TP->catch_msg("A fiery power enters your spirit.\n");
   TP->add_mana(200);
   if(random(2)){
      old = TP->query_skill(130005);
      TP->set_skill(130005, old + 1);
   }
}

