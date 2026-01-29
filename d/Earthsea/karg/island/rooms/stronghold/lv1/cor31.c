#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. It seems to continue to northwest , while to "+
   "northeast you see big room with lines of shelves and to the west "+
   "you see some small round room.\n");

 add_exit(STRHOLD_LVL1+"cor32","northwest");
 add_exit(STRHOLD_LVL1+"library","northeast");
 add_exit(STRHOLD_LVL1+"up2","west");
}

