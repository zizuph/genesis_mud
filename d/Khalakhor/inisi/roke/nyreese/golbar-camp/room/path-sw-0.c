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
    
    add_extra("The path continues to the northeast and to the west the path leads out of the thick bushes.\n");

    add_exit(NYREESEDIR + "orc_road3", "west", 0, 0, 1);
    add_exit(CAMP_ROOM + "path-sw-1", "northeast", 0, 0, 1);
}