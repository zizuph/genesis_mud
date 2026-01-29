#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Dark corridor in the stronghold");
 set_long("You are in the dark corridor leading north and south. "+
    "You see banners on the walls , while on arch leading north you "+
    "see flag.\n");

 add_item(({"wall","walls"}),"Walls are decorated with colourfull "+
   "banners.\n");
 add_item(({"banner","banners"}),"Banners are of different colours "+
   "and sway slightly in the gusts of wind , freely blowing down "+
   "the corridor.\n");
 add_item("arch","It leads north , where the corridor seem to end.\n");
 add_item("flag","Flag of Karg Empire flows slightly in gusts of "+
   "wind.\n");

 add_exit(STRHOLD_LVL1+"cor6","south");
 add_exit(STRHOLD_LVL1+"cor8","north");
}

