#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small corridor on the third level "+
   "of the stronghold. Cirridor continues to south and north.\n");

 add_exit(STRHOLD_LVL3+"cor17","north");
 add_exit(STRHOLD_LVL3+"cor19","south");
}

