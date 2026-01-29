inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
void
create_object()
{
   ::create_object();
   set_name("locket");
   add_name("_guard_quest_locket");
   set_adj("jeweled");
   set_long("This is a beautiful jeweled locket. Strange that the "
	+"guard had this.\n");
   add_prop(OBJ_I_VALUE,3000);
   add_prop(OBJ_I_VOLUME,3000);
   add_prop(OBJ_I_WEIGHT,3000);
}
