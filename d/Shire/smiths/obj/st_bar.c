inherit "/std/object";

#include "stdproperties.h"
#include "/d/Shire/common/defs.h"
#include <smiths.h>

#define ITEM_TYPE "steel"

int smiths_item_bonus=STEEL;

void
create_object() {

   set_name(({"bar","smiths_steel_bar"}));
   add_name("steel");
   set_adj("steel");

   set_long("This steel bar is marked with the sign of the smiths guild."+
      " It is of the kind used for forging items.\n");

   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_VALUE,STEEL_COST);
}

string
query_smiths_item() {
   return ITEM_TYPE;
}
