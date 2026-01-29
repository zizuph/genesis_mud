inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_short("ruined pile of armour");
   set_name("armour");
   add_name("ruined pile");
   add_name("pile");
   add_name("ruined pile of armour");
   set_long("A full suit of extravagantly decorated iron armour, "+
      "unfortunately for you it has been almost totally ruined.\n");
   add_prop(OBJ_I_WEIGHT,2500000);
   add_prop(OBJ_I_VOLUME,2500000);
}
