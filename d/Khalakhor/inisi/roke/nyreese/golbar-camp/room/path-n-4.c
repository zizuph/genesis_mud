 /*
  * Room in the northern path to the camp
  */
#pragma strict_types

#include "defs.h"

inherit PATH_BASE;

void
create_room()
{
    ::create_room();
    
    add_extra("The path continues to the both west and east.\n");

    add_exit(CAMP_ROOM + "path-n-3", "west", 0, 0, 1);
    add_exit(CAMP_ROOM + "path-n-5", "east", 0, 0, 1);
}