#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. This corridor is dusty and full of junk. It "+
   "continues to east , while to southwest it seems to end with a "+
   "dead end!\n");

 add_exit(STRHOLD_LVL1+"cor35","east");
 add_exit(STRHOLD_LVL1+"dend","southwest");
}

