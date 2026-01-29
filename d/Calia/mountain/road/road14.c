 /* 
    Digit 02 FEB 95 
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
    make_the_room("This bleak unpopulated territory stretches all " +
           "around for many miles, and the road passes through it " +
           "from northwest to southeast. A great distance to the " +
           "southeast you can just make out the grim figure of " +
           "Mount Kyrus.\n");

    add_item(({"mount kyrus", "mountain", "mount"}),
           "The great grey mountain can be " +
           "be seen rising a great distance away to the southeast.\n");

    add_exit(ROAD+"road15","northwest");
    add_exit(ROAD+"road13","southeast");
    add_exit(ROAD+"m19", "west");
    add_exit(ROAD+"m24", "southwest");
    add_exit(ROAD+"m25", "south");
    add_exit(ROAD+"m20", "east");
    add_exit(ROAD+"m15", "northeast");
    add_exit(ROAD+"m14", "north");
    
}
