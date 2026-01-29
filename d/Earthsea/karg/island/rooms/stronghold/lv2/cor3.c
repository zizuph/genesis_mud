#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Broad corridor in the stronghold");
 set_long("You are in the dark and broad corridor on the second level "+
   "of the stronghold. Walls are decorated with banners and flags. "+
   "Corridor here seems to split as new one leads towards northwest.\n");

 add_item(({"wall","walls"}),"Walls are decorated with colourfull "+
   "banners and flags.\n");
 add_item(({"banners","flags"}),"Banners and flags are of different "+
   "colours and sway slightly in the gusts of wind , freely blowing "+
   "down the corridor.\n");

 add_exit(STRHOLD_LVL2+"cor2","east");
 add_exit(STRHOLD_LVL2+"cor4","southwest");
 add_exit(STRHOLD_LVL2+"cor19","northwest");
}

