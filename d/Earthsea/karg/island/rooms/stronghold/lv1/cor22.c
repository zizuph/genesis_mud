#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small and dark corridor in the stronghold. "+
   "It is very dusty and narrow.\n");

 add_exit(STRHOLD_LVL1+"cor21","west");
 add_exit(STRHOLD_LVL1+"cor23","northeast");
}

