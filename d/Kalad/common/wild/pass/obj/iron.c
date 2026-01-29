inherit "/std/object.c";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("iron");
   add_name("_cast_iron");
   add_name("shred");
   set_short("shred of cast iron");
   set_long("A cast off piece of scrap iron, probably just worth a few "+
      "copper coins.\n");
   add_prop(OBJ_I_VALUE,5);
   add_prop(OBJ_I_VOLUME,250);
   add_prop(OBJ_I_WEIGHT,300);
}
