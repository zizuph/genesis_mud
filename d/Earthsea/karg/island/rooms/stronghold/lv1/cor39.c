#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. To your south you see some kind of armoury.\n");

 add_exit(STRHOLD_LVL1+"cor14","southwest");
 add_exit(STRHOLD_LVL1+"armoury","south");
}

