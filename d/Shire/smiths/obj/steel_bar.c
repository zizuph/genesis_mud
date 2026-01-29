inherit "/std/object";

#include <stdproperties.h>
#include "/d/Shire/smiths/smiths.h"

void
create_object() {

   set_name(({"bar","smith_bar","steel_smith_bar"}));
   set_adj("steel");
   set_short("steel bar");

   set_long("This steel bar is marked with the sign of the Smiths "+
      "Guild. It can be used for forging items.\n");

   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_VALUE, 200);
}
