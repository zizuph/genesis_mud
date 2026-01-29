/*  Digit 02 FEB 95 
    Modified Maniac 3/3/95, 28/4/95 
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("The road leads northwest towards the west docks of " +
             "Calia and its capital Gelan, and southeast further into " +
             "this bleak unpopulated territory. To the south stands " +
             "the monument to the fallen.\n"); 
    add_exit(ROAD+"road17","northwest");
    add_exit(ROAD+"road15","southeast");
    add_exit(ROAD+"m07", "west");
    add_exit(ROAD+"m02", "north");
    add_exit(ROAD+"m03", "northeast");
    add_exit(ROAD+"m08", "east");
    add_exit(ROAD+"m12", "southwest");
    add_exit(ROAD+"m13", "south"); 
}
