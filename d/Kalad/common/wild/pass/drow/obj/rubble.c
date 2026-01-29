inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_short("pile of rubble");
   set_name("rubble");
   add_name("pile");
   set_long("A large pile of obsidian rubble.\n");
   add_prop(OBJ_I_WEIGHT,2000000);
   add_prop(OBJ_I_VOLUME,2000000);
}
