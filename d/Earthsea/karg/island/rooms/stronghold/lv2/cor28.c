#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small corridor on the second level "+
   "of the stronghold. Corridor continues to southwest and south , "+
   "while to northeast you see room with guards.\n");

 add_exit(STRHOLD_LVL2+"cor27","southwest");
 add_exit(STRHOLD_LVL2+"guard3","northeast");
 add_exit(STRHOLD_LVL2+"cor29","south");
}

