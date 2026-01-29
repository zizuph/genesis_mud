 /*
  * Room in the south path to the camp
  */
#pragma strict_types
  
#include "defs.h"

inherit PATH_BASE;

void
create_room()
{
    ::create_room();
    
    add_extra("The path continues to the southwest and north.\n");

    add_exit(CAMP_ROOM + "path-s-0", "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM + "path-s-2", "north", 0, 0, 1);
}