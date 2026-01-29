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
    
    add_extra("The path continues to the west and to the east.\n");

    add_exit(CAMP_ROOM + "path-n-4", "west", 0, 0, 1);
    add_exit(CAMP_ROOM + "path-n-6", "east", 0, 0, 1);
}