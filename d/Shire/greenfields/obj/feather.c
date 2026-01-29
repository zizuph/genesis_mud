inherit "/std/object";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

void
create_object()
{

   set_name("feather");
   add_name(({"_pott_feather_","shirriffe feather"}));
   set_short("bloody feather");
   add_adj("bloody");
   set_long("This bloody feather is like those worn in the "+
   "caps of Shirriffes. It appears to be the feather of "+
   "a large bird, like a turkey.\n");

   add_prop(OBJ_I_WEIGHT, 10); /* Light as a feather */
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_VALUE, 12);

}
