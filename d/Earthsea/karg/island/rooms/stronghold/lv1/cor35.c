#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. This corridor is dusty and full of junk. It "+
   "continues to west.\n");

 add_exit(STRHOLD_LVL1+"cor6","northeast");
 add_exit(STRHOLD_LVL1+"cor36","west");
}

