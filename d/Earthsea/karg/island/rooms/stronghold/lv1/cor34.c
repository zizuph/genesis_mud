#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. The corridor looks like it was abandoned long "+
   "time ago. Walls are far away from being finished, they have lots "+
   "of holes and look like they gonna crash down from a simple touch.\n");

 add_exit(STRHOLD_LVL1+"cor38","north");
 add_exit(STRHOLD_LVL1+"admiral","east");
}

