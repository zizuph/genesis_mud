inherit "/std/object";

#include "stdproperties.h"
#include "/d/Shire/common/defs.h"
#include <smiths.h>

#define ITEM_TYPE "grey"

int smiths_item_bonus=GREYALLOY;

void
create_object() {

   set_name(({"bar","smiths_greyalloy_bar"}));
   add_name("grey alloy");
   set_adj("alloy");
   set_adj("grey");

   set_long("This grey alloy metal bar is marked with the sign of the"+ 
      " smiths guild. It is of the kind used for forging items.\n");

   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_VALUE,GREYALLOY_COST);
}

string
query_smiths_item() {
   return ITEM_TYPE;
}
