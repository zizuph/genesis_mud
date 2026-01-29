inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   ::create_object();
   set_name("ashes");
   add_name("pile");
   set_short("pile of ashes");
   set_pshort("piles of ashes");
   set_long("It appears to be the near-vaporized remains of something, "+
      "or someone.\n");
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
}
