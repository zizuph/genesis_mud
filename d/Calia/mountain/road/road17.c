 /* Digit 02 FEB 95 
    Modified Maniac 3/3/95
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("You are not far from the docks of Calia and its " +
          "capital Gelan now, away to the north. " +
          "Heading southwards will take you further " +
          "into this bleak unpopulated territory. The road runs from " +
          "north to southeast.\n");
    add_exit(ROAD+"road18","north");
    add_exit(ROAD+"road16","southeast");
    add_exit(ROAD+"m01", "west");
    add_exit(ROAD+"m02", "east");
    add_exit(ROAD+"m06", "southwest");
    add_exit(ROAD+"m07", "south");
    
}
