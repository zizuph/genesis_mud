#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Broad corridor in the stronghold");
 set_long("You are in the dark and broad corridor on the second level "+
   "of the stronghold. Corridor keeps running towards southwest and "+
   "southeast , while to northwest and northeast you see some kind of "+
   "small round rooms.\n");

 add_item(({"wall","walls"}),"Walls are decorated with colourfull "+
   "banners and flags.\n");
 add_item(({"banners","flags"}),"Banners and flags are of different "+
   "colours and sway slightly in the gusts of wind , freely blowing "+
   "down the corridor.\n");

 add_exit(STRHOLD_LVL2+"cor9","southwest");
 add_exit(STRHOLD_LVL2+"cor11","southeast");
 add_exit(STRHOLD_LVL2+"up1","northwest");
 add_exit(STRHOLD_LVL2+"up2","northeast");
}

