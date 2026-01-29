#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. It seems to continue to southeast , while to "+
   "northeast you see large hall.\n");

 add_exit(STRHOLD_LVL1+"cor5","west");
 add_exit(STRHOLD_LVL1+"warroom","northeast");
 add_exit(STRHOLD_LVL1+"cor31","southeast");
}

