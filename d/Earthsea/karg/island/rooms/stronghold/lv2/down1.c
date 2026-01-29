#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("In small round room");
 set_long("You are in small round room. You barely fit here , the "+
   "only thing is this room is ladder leading downwards.");

 add_item("ladder","The ladder leads down through the hole in the "+
   "floor.\n");

 add_exit(STRHOLD_LVL2+"cor1","northeast");
 add_exit(STRHOLD_LVL1+"up1","down");
}

