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

create_food() {
   set_name(randname());
   add_name(({"vegetable", "food"}));
   set_adj("raw");
   set_long("This is a raw vegetable.\n");
   add_prop(OBJ_I_VALUE, 0);
   set_amount(20);
   add_prop(OBJ_I_WEIGHT,80);
   add_prop(OBJ_I_VOLUME,100);
}

string                                                                          
randname()
{                                                                               
   string *randname;
   randname = ({"potato", "carrot", "cabbage", "onion"});
   return randname[random(sizeof(randname))];
                                                                               
}

