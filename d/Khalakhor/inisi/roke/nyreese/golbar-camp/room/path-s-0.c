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
    
    add_extra("The path continues to the northeast. From the south you hear the sounds of waves rolling over a beach.\n");

    add_exit(CAMP_ROOM + "beach-landing", "south", 0, 0, 1);
    add_exit(CAMP_ROOM + "path-s-1", "northeast", 0, 0, 1);
}