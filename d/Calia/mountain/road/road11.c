/* Digit 02 FEB 95 
   Modified Maniac 7/3/95, 2/5/95
*/

#pragma save_binary

inherit "/d/Calia/std/std_foothills";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

void
create_room()
{

    make_the_room("The cobbled road you are on runs from " +
                  "northwest to southeast.\n", 
                  "northwest", 2);

    add_exit(ROAD+"road10","southeast");
    add_exit(ROAD+"road12","northwest");
    add_exit(ROAD+"m35", "west");
    add_exit(ROAD+"m32", "north");
    add_exit(FOOTHILL+"fh01", "northeast");
    add_exit(FOOTHILL+"fh10", "east");
    add_exit(FOOTHILL+"fh19", "southwest");
    add_exit(FOOTHILL+"fh20", "south");
}
