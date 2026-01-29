#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. To your southwest you see some kind of storage "+
   "room.\n");

 add_exit(STRHOLD_LVL1+"cor3","east");
 add_exit(STRHOLD_LVL1+"storage","southwest");
}

