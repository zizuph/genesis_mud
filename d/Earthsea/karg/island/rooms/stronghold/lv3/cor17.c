#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small corridor on the third level "+
   "of the stronghold. To east , west and north in connects with "+
   "main circle corridor , and continues futher to south in to the "+
   "darkness.\n");

 add_exit(STRHOLD_LVL3+"cor1","north");
 add_exit(STRHOLD_LVL3+"cor2","east");
 add_exit(STRHOLD_LVL3+"cor16","west");
 add_exit(STRHOLD_LVL3+"cor18","south");
}

