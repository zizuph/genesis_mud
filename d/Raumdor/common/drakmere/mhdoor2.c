/* Sarr */
#include "defs.h"
inherit "/std/door";

void
create_door()
{
   set_door_id("manhole");
   set_pass_command(({"u","up"}));
   set_door_name(({"iron manhole","manhole"}));
   set_other_room(DRAKMERE_DIR + "road14");
   set_door_desc("It is a large iron manhole cover. If you open it, "+
   "you could go up above to the surface.\n");
   set_fail_pass("The manhole is closed.\n");
   set_open(0);
}
