inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object() {
   set_name("shovel");
   set_adj("rusted");
   set_adj("filthy");
   set_long("This object barely qualifies as a shovel. " +
      "It is made of an old rotting long handle and a rusted, bent shovel head tied together.\n");
   add_prop(OBJ_I_VALUE,  25);
   add_prop(OBJ_I_WEIGHT, 1750);
   add_prop(OBJ_I_VOLUME, 1400);
}
