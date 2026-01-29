#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("In small round room");
 set_long("You are in small round room. You barely fit here , the "+
   "only thing is this room is ladder leading upwards.");

 add_item("ladder","The ladder leads up through the hole in the "+
   "ceiling.\n");

 add_exit(STRHOLD_LVL2+"cor10","southwest");
 add_exit(STRHOLD_LVL3+"down2","up");
}

