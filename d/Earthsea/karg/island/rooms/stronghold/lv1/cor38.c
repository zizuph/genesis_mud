#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. This part of corridor seems to be done only "+
   "partily. Walls look like they gonna crash down any second.\n");

 add_exit(STRHOLD_LVL1+"cor33","east");
 add_exit(STRHOLD_LVL1+"cor34","south");
}

