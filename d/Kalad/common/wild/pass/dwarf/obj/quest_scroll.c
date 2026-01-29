inherit "/std/object.c";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by korat */
void
create_object()
{
   ::create_object();
   set_name("scrolls");
   add_name("scrolls of wisdom");
   set_short("scrolls of wisdom");
   set_long("This is the Scrolls of Wisdom. On them "+
      "you find the words of the dwarven God Rahxvan, "+
      "written in old and everlasting runes. You "+
      "try to read them, but you don't understand "+
      "any of it.\n");
   add_prop("korat_quest_scroll",1);
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_VOLUME,2000);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_M_NO_SELL,1);
}
