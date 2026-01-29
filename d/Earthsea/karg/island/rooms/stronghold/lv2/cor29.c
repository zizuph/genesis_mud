#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small corridor on the second level "+
   "of the stronghold. Corridor looks old and long time ago "+
   "abandoned.\n");

 add_exit(STRHOLD_LVL2+"cor28","north");
 add_exit(STRHOLD_LVL2+"cor30","south");
}

