#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small corridor on the third level "+
   "of the stronghold. Cirridor continues to east, while to west "+
   "you see small round room.\n");

 add_exit(STRHOLD_LVL3+"cor26","east");
 add_exit(STRHOLD_LVL3+"down2","west");
}

