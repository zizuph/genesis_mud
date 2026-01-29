#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small corridor on the third level "+
   "of the stronghold. To east , west and south in connects with "+
   "main circle corridor , and continues futher to north in to the "+
   "darkness.\n");

 add_exit(STRHOLD_LVL3+"cor21","north");
 add_exit(STRHOLD_LVL3+"cor8","east");
 add_exit(STRHOLD_LVL3+"cor10","west");
 add_exit(STRHOLD_LVL3+"cor9","south");
}

