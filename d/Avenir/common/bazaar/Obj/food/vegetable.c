// file name: /d/Avenir/common/bazaar/Obj/food/mollusk.c
 // creator(s):   Glinda, May , 1995
// last update:
// purpose: Food to get from a bucket
// note:
// bug(s):
// to-do:

inherit "/std/food";

#include "/sys/stdproperties.h"

string randname();

create_food() {
  string name;

  name = randname();
   set_name(name);
   add_name(({"vegetable", "food"}));
   set_adj("raw");
   set_long("This is a raw vegetable.\n");
   add_prop(OBJ_I_VALUE, 0);
   set_amount(20);
   add_prop(OBJ_I_WEIGHT,80);
   add_prop(OBJ_I_VOLUME,100);
   add_prop(HEAP_S_UNIQUE_ID, "_glinda_food_" + name);
}

string                                                                          
randname()
{                                                                               
   string str;

   switch(random(4))
   {
      case 0: str="potato";  break;
      case 1: str="carrot";  break;
      case 2: str="cabbage"; break;
      case 3: str="onion";   break;
   }
   return str;
                                                                               
}

