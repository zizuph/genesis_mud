#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small corridor on the third level "+
   "of the stronghold. Cirridor continues to east and to west "+
   "connects with main circle corridor.\n");

 add_exit(STRHOLD_LVL3+"cor24","east");
 add_exit(STRHOLD_LVL3+"cor13","west");
}

