inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"


void
create_object()
{
   set_short("roughly drawn map");
   add_adj(({"roughly","drawn"}));
      set_name(({"map","_mapping_quest_map_"}));
   add_name("_mapping_quest_map_");
   set_long("This map looks like chicken scratching. You can make out some "+
   "dots and dashes- it looks like a camp.\n");


   add_prop(OBJ_I_VALUE, 12);
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_WEIGHT, 14);

}
