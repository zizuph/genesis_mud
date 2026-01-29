 /* Digit 02 FEB 95 
    Modified, Maniac 7/3/95, 25/4/95
 */

#pragma save_binary

inherit "/d/Calia/std/std_foothills";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("The cobbled road you are on runs from northwest " +
                  "to southeast.\n", 
                  "northwest", 1);
    add_exit(ROAD+"road9","southeast");
    add_exit(ROAD+"road11","northwest");
    add_exit(FOOTHILL+"fh20", "west");
    add_exit(FOOTHILL+"fh11", "northeast");
    add_exit(FOOTHILL+"fh10", "north");
    add_exit(FOOTHILL+"fh22", "east");
    add_exit(FOOTHILL+"fh33", "southwest");
    add_exit(FOOTHILL+"fh34", "south");
}