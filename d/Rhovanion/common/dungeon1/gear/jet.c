inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object() {
   set_name("stone");
   set_adj("jet");
   set_long("This is a small jet stone about an inch or two in diameter " +
      "and uncut.  It is jet black and, when properly cut you calculate, " +
      "would be beautifully smooth and worth a lot to someone.  Right now " +
      "though, it isn't worth too much.\n");
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT, 400);
   add_prop(OBJ_I_VOLUME, 300);
}
