inherit "/std/object";

#include <stdproperties.h>
#include "/d/Shire/guild/smiths/smiths.h"

void
create_object() {

   set_name(({"bar","smith_bar","iron_smith_bar"}));
    add_name("smiths_iron_bar");
    // get rid of this once reformated info is in place
   set_adj("iron");
   set_short("iron bar");

   set_long("This iron bar is marked with the sign of the smiths guild."+
      " It is of the kind used for forging items.\n");

   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_VALUE, 100);
}
