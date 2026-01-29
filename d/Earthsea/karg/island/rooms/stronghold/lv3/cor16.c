#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Circle corridor in the stronghold");
 set_long("You are in the main circle corridor on the third level "+
   "of the stronghold. Corridor continues to northeast and "+
   "southwest , while smaller corridor splits towards east.\n");

 add_item(({"wall","walls"}),"Walls are decorated with colourfull "+
   "banners.\n");
 add_item(({"banner","banners"}),"Banners are of different colours "+
   "and sway slightly in the gusts of wind , freely blowing down "+
   "the corridor.\n");

 add_exit(STRHOLD_LVL3+"cor1","northeast");
 add_exit(STRHOLD_LVL3+"cor17","east");
 add_exit(STRHOLD_LVL3+"cor15","southwest");
}

