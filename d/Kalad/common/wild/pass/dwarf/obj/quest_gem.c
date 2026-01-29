inherit "/std/object.c";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
/* by korat */
void
create_object()
{
   ::create_object();
   set_name("gem");
   add_name("red gem");
   set_long("An absolutely gorgeous blood-red gem. Its many-faceted surface "+
      "seems to catch the faintest of lights and intensifies them into a "+
      "brilliance that astounds the eye.\n");
   add_prop("korat_quest_gem",1);
   add_prop(OBJ_I_VALUE,2000);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_I_WEIGHT,500);
}
