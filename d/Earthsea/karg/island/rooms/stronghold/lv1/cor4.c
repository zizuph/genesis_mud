#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Dark corridor in the stronghold");
 set_long("You are in the dark corridor leading north and south. "+
   "To the west you see some small round room.\n");

 add_item(({"wall","walls"}),"Walls are decorated with colourfull "+
   "banners. On one of the walls you see picture\n");
 add_item(({"banner","banners"}),"Banners are of different colours "+
   "and sway slightly in the gusts of wind , freely blowing down "+
   "the corridor.\n");

 add_exit(STRHOLD_LVL1+"cor3","south");
 add_exit(STRHOLD_LVL1+"cor5","north");
 add_exit(STRHOLD_LVL1+"up1","west");
}

