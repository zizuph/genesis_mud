inherit "/std/object";

#include "stdproperties.h"
#include "/d/Shire/common/defs.h"
#include <smiths.h>

#define ITEM_TYPE "greyish"

int smiths_item_bonus=IRON;

void
create_object() {

   set_name(({"bar","smiths_melted_bar"}));

   set_long("This "+short()+" is the remains of a melted armour or"+
      " weapon. A smiths might find it useful for the forging of an item.\n");

   add_prop(OBJ_I_WEIGHT,5000+random(5000));
   add_prop(OBJ_I_VOLUME,750+random(750));
   add_prop(OBJ_I_VALUE,COPPER_COST);
}

string
query_smiths_item() {
   return ITEM_TYPE;
}
