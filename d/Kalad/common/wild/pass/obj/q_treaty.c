inherit "/std/scroll";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_scroll()
{
   set_name("parchment");
   add_name("blood-red parchment");
   add_name("piece of parchment");
    add_name("quest_parchment");
   add_name("blood-red piece of parchment");
   set_short("blood-red piece of parchment");
   set_long("The torn remains of some official-looking parchment. There "+
      "appears to be some red writing on it.\n");
   
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
   
   set_file("/d/Kalad/common/wild/pass/obj/q_treaty");
}
