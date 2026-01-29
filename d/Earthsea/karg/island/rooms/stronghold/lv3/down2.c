#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("In small round room");
 set_long("You are in small round room. You barely fit here , the "+
   "only thing is this room is ladder leading downwards. Three "+
   "corridors start their ways here - to northwest , southwest and "+
   "east.\n");

 add_item("ladder","The ladder leads down through the hole in the "+
   "floor.\n");

 add_exit(STRHOLD_LVL3+"cor19","northwest");
 add_exit(STRHOLD_LVL3+"cor20","southwest");
 add_exit(STRHOLD_LVL3+"cor25","east");
 add_exit(STRHOLD_LVL2+"up2","down");
}

