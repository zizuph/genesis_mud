
inherit "/std/food";
#include <stdproperties.h>

create_food()
{
   set_name("mint");
   set_adj("thin");
   set_long("Its a wafer thin after dinner mint.\n");
   set_amount(300); /* 50 grams of food. */
   add_prop(OBJ_I_WEIGHT, 300); 
   add_prop(OBJ_I_VOLUME, 100);
}
