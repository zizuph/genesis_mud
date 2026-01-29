inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   set_name("bones");
   add_name("heap");
   set_short("heap of bones");
   set_pshort("heaps of bones");
   set_long("The many smashed and battered remnants of a skeleton.\n");
   add_prop(OBJ_I_WEIGHT,30000);
   add_prop(OBJ_I_VOLUME,30000);
}
