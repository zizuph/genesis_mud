inherit "/std/object";

#include "stdproperties.h"
#include "/d/Shire/common/defs.h"
#include <smiths.h>

#define ITEM_TYPE "copper"

int smiths_item_bonus=COPPER;

void
create_object() {

   set_name(({"bar","smiths_copper_bar"}));
   add_name("copper");
   set_adj("copper");

   set_long("This copper bar is marked with the sign of the smiths guild."+
      " It is of the kind used for forging items.\n");

   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_VALUE,COPPER_COST);
}

string
query_smiths_item() {
   return ITEM_TYPE;
}
