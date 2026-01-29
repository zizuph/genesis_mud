 /*
  * Room in the southwestern path to the camp
  */
#pragma strict_types
  
#include "defs.h"

inherit PATH_BASE;

void
create_room()
{
    ::create_room();
    
    add_extra("The path continues to the southwest and east.\n");

    add_exit(CAMP_ROOM + "path-sw-0", "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM + "path-sw-2", "east", 0, 0, 1);
}