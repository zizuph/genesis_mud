#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("hallway");
   set_long(BS(
         "You are at a bend in the corridor. East is a large pair of doors and"
         + " the main corridor.  The hallway ends to the south in a door.  There"
         + " is a very sturdy door to the west.",75));
   
   add_item(({"door","doors"}),"They seem to be plentiful around here, "
      + "it is a mansion afterall.\n");
   
   add_exit(ICE_CAST2_R + "hall4_2.c", "east");
   add_exit(ICE_CAST2_R + "trophy.c", "west");
   add_exit(ICE_CAST2_R + "hall6_2.c", "south");
}
