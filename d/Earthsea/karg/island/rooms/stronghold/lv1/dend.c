#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Dead end");
 set_long("The corridor seems to end with a dead end! Room is empty "+
   "except some heap of junk, thrown on the ground.\n");

 add_item(({"heap","junk"}),"It's stinky heap of junk. You don't wanna "+
   "come closer!\n");

 add_exit(STRHOLD_LVL1+"cor36","northeast");
}

