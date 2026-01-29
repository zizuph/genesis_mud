inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object() {
   set_name("stone");
   set_adj("quartz");
   set_long("This is a well-cut, well-cut for a quartz " +
      "that is, white quartz about an inch across that may " +
      "be worth a bit of coinage.\n");
   add_prop(OBJ_I_VALUE, 750);
   add_prop(OBJ_I_WEIGHT, 400);
   add_prop(OBJ_I_VOLUME, 300);
}
