/* Vladimir 8-09-94 */
inherit "/std/room.c";

#include <macros.h>
#include "local.h"
#include "/sys/stdproperties.h"
#define TO this_object()

string long;
object rat;
create_room()
{
   set_short("Fortress hall");
   set_long("You stand within the last part of this damp corrider. To\n"
      + "your north is a doorframe with no door. On the wall directly\n"
      + "to your left is a small hole. The ceiling gets lower here,\n"
      + "but you are still able to stand.\n");
   add_item(({"doorframe", "frame"}),
      break_string("You are looking at a crooked door frame that "+
         "does not have a door in it. You think you hear "+
         "some noises just north of it.\n", 70));
   add_item(({"wall"}),
      break_string("It is a rough wall with a hole near the bottom "+
         "of it.\n", 70));
   add_item(({"hole", "small hole"}),
      break_string("This is a small hole just large enough for "+
         "vermon to scrape through.\n", 70));
   add_item(({"ceiling", "up"}),
      break_string("The ceiling gradualy slopes donward.\n", 70));
   
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(ORC+"hall2", "south");
   add_exit(ORC+"guardroom", "north");
   
   reset_room();
}

reset_room()
{
   if(!rat)
      {
      rat = clone_object(ORC+"monsters/ratty");
      rat-> move_living("xxx", TO);
   }
}

