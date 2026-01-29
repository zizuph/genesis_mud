#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Circle corridor in the stronghold");
 set_long("You are in the main circle corridor on the third level "+
   "of the stronghold. Corridor continues to northwest and "+
   "makes a sharp turn to southwest. Smaller corridor splits "+
   "to west and runs into the darkness.\n");

 add_item(({"wall","walls"}),"Walls are decorated with colourfull "+
   "banners.\n");
 add_item(({"banner","banners"}),"Banners are of different colours "+
   "and sway slightly in the gusts of wind , freely blowing down "+
   "the corridor.\n");

 add_exit(STRHOLD_LVL3+"cor4","northwest");
 add_exit(STRHOLD_LVL3+"cor6","southwest");
 add_exit(STRHOLD_LVL3+"cor26","west");
}

