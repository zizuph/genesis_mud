#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in rather small and dusty corridor. To your "+
   "west you see some kind of smithy , while to southeast you see "+
   "large hall.\n");

 add_exit(STRHOLD_LVL2+"smithy","west");
 add_exit(STRHOLD_LVL2+"cor25","southeast");
}

