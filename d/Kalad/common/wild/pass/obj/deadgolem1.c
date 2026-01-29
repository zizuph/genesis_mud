inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_short("useless pile of armour");
   set_name("armour");
   add_name("useless pile");
   add_name("pile");
   add_name("useless pile of armour");
   set_long("A complete suit of lavishly decorated bronze armour, "+
      "unfortunately for you it is completely in ruins.\n");
   add_prop(OBJ_I_WEIGHT,2000000);
   add_prop(OBJ_I_VOLUME,2000000);
}
