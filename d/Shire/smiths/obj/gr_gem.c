inherit "/std/object";

#include "stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "smiths.h"

#define ITEM_TYPE "green gem"

void
create_object() {

   set_name(({"gem","smiths_green_gem"}));
   set_adj("green");

   set_long("This is some sort of semi-precious gem. It would look nice"+
      " in the hilt of a weapon.\n");

   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
   add_prop(OBJ_I_VALUE,GEM_COST);
}

string
query_smiths_item() {
   return ITEM_TYPE;
}

