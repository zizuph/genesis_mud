 /* Digit 02 FEB 95 
    Modified Maniac 3/3/95 */

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("Far to the southeast you " +
         "see the giant figure of Mount Kyrus rising into the sky, " +
         "beginning to dominate the landscape. The cobbled road you " +
         "are on runs from northwest to southeast.\n");

    add_item(({"mount kyrus", "mountain", "mount"}),
           "The great grey mountain can be seen rising a " +
           "long way to the southeast. Despite it being a long " +
           "distance away it is beginning to dominate the " +
           "landscape in that direction.\n");

    add_exit(ROAD+"road14","northwest");
    add_exit(ROAD+"road12","southeast");
    add_exit(ROAD+"m25","west");
    add_exit(ROAD+"m26","east");
    add_exit(ROAD+"m20","north");
    add_exit(ROAD+"m31","south");
    add_exit(ROAD+"m30","southwest");
    add_exit(ROAD+"m21","northeast");
}
