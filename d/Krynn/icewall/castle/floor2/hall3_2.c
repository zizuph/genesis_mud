#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("hallway");
   set_long(BS(
         "You are standing in the upstairs hallway. North of you is a door while"
         + " the corridor runs west to the main staircase.",75));
   
   add_item("door","It is quite solid and virtually impenetrable.\n");
   add_cmd_item("door","open","You open the door.\n");
   add_cmd_item("door","close","You close the door.\n");
   
   add_exit(ICE_CAST2_R + "room1.c", "north");
   add_exit(ICE_CAST2_R + "hall1_2.c", "west");
}
