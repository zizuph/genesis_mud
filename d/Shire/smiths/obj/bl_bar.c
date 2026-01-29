inherit "/std/object";

#include "stdproperties.h"
#include "/d/Shire/common/defs.h"
#include <smiths.h>

#define ITEM_TYPE "blue steel"

int smiths_item_bonus=BLUESTEEL;

void
create_object() {

   set_name(({"bar","smiths_bluesteel_bar"}));
   add_name("blue steel");
   set_adj("steel");
   set_adj("blue");

   set_long("This blue steel bar is marked with the sign of the smiths"+ 
      " guild. It is of the kind used for forging items.\n");

   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_VALUE,BLUESTEEL_COST);
}

string
query_smiths_item() {
   return ITEM_TYPE;
}
