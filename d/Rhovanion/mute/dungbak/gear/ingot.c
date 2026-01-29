inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object() {
   set_name("ingot");
   set_adj("silver");
   set_long("This is a bar of unpure, low-grade silver with no special markings or writing on it.  Despite all that, you think it still ought to be worth something.\n");
   add_prop(OBJ_I_VALUE, 333);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 400);
}
