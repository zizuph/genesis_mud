// file name: /d/Avenir/common/bazaar/Obj/food/mollusk.c
// creator(s): Ilyian, May 17, 1995
// last update:
// purpose: Food to get from a bucket
// note:
// bug(s):
// to-do:

inherit "/std/food";

#include "/sys/stdproperties.h"

string randname();
string randlong();

create_food() {
   name=randname();
   set_name(name());
   add_name(({"vegetable", "food"}));
   set_adj("raw");
   set_long(randlong());
   add_prop(OBJ_I_VALUE, 0);
   add_prop(HEAP_S_UNIQUE_ID, "glinda_food_" + name);
   set_amount(20);
   add_prop(OBJ_I_WEIGHT,80);
   add_prop(OBJ_I_VOLUME,100);
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

string
randlong()
{
   string str;
 
   switch(random(3)); 
   {
      case 0: str="This is a raw vegetable, much like any other you have previously seen.\n";
         break;
      case 1: str="It is a common vegetable, rather uninteresting, but edible.\n";
         break;
      case 2: str="It is uncooked, but still edible. It might give you gas though.\n";
         break;
    }
   return str;
}
