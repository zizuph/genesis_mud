#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small and dark corridor in the stronghold. "+
   "It is very dusty and narrow. Corridor seems to end to the "+
   "southwest.\n");

 add_exit(STRHOLD_LVL1+"ent3","southwest");
 add_exit(STRHOLD_LVL1+"cor20","east");
}

