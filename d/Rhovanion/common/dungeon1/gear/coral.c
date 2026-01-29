inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object() {
   set_name("symbol");
   set_adj("coral");
   set_adj("red");
   set_long("This symbol is in the shape of a dragon and reminiscent " +
      "of the medals worn by Solamnic Knights in the service of " +
      "Paladine except there is no chain.\n" +
      "     The symbol itself is fashioned out of a solid piece of " +
      "luscious red coral.  Whoever made it put a lot of effort into " +
      "the gathering of materials and the meticulous painstaking work " +
      "of carving it just perfectly.  It makes you curious as to what " +
      "it was doing on the individual you `found' it on.\n");
   add_prop(OBJ_I_VALUE, 1000);
   add_prop(OBJ_I_WEIGHT, 400);
   add_prop(OBJ_I_VOLUME, 275);
}
