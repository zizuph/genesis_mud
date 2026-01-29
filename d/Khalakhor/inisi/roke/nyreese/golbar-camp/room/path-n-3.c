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
    
    add_extra("The path continues to both east and west.\n");

    add_exit(CAMP_ROOM + "path-n-2", "west", 0, 0, 1);
    add_exit(CAMP_ROOM + "path-n-4", "east", 0, 0, 1);
}