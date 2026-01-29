inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */

create_object()
{
   set_name("mummycorpse");
   add_name("corpse");
   set_adj("mummified");
   set_short("mummified corpse");
   set_pshort("mummified corpses");
   set_long("The long-dead remains of a human being. Due to the "+
      "extremely dry environment of the Great Kalad Waste, and this "+
      "corpse's isolated location, it has decayed very little.\n");
   add_prop(OBJ_I_WEIGHT,30000);
   add_prop(OBJ_I_VOLUME,30000);
   add_prop(OBJ_M_NO_TELEPORT,1);
}
