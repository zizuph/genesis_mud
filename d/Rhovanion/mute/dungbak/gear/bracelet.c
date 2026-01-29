inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object() {
   set_name("bracelet");
   set_adj("copper link");
   set_long("This is a small bracelet, probably made for a woman, " +
      "with groups of three ornately twisting rings linked together " +
      "to form the bracelet itself.  It would make a nice gift if it " +
      "weren't for the fact that the clasp that fastens the bracelet " +
      "together is missing.  It's probably still worth something though.\n");
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT, 555);
   add_prop(OBJ_I_VOLUME, 315);
}
