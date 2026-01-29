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
   set_name("shred");
   set_adj("small");
   set_long("A small shred of stone. It seems to have been "+
      "chipped of something, because one of the sides are "+
      "extremeley smooth to the touch.\n");
   add_prop("korat_quest_shred",1);
   add_prop(OBJ_I_VALUE,1);
   add_prop(OBJ_I_VOLUME,20);
   add_prop(OBJ_I_WEIGHT,30);
   add_prop(OBJ_M_NO_SELL,1);
}
