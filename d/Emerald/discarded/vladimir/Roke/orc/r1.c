/* Vladimir 8-16-94 */
inherit "/std/room.c";

#include <macros.h>
#include "/sys/stdproperties.h"
#include "local.h"

create_room()
{
   set_short("Fortress hallway");
   set_long("You can faintly hear the sounds of the bright and vivid world\n"
      + "outside. Then you are confronted with the sights and smells of\n"
      + "reality. There is a rancid odor in the air, it is the smell\n"
   +"of the orc. You try to force it out of your lungs, but inhale\n"
      + "it once again as you are forced to breathe. Their is a small\n"
      + "hallway leading north. You may go back the way you came as well\n"
      + "as continue further on.\n");
   
   add_item(({"hallway", "hall"}),
    "It is a long hallway ahead of you.\n");
  add_prop(ROOM_I_INSIDE, 1);
   add_exit(ORC+"hall1", "north");
   add_exit(ORC+"r2", "west");
   
}
