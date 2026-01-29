/* 
   Created Digit
   Modified Maniac   7/3/95, 25/4/95 
*/

#pragma save_binary

inherit "/d/Calia/std/std_foothills";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("Rising steeply to the southeast you see " +
                  "the beginnings of a crystalline road " +
                  "that leads up the mountain side, winding " +
                  "gradually around the mountain. The cobbled " +
                  "road you are on runs from northwest to " + 
                  "southeast.\n",
                  "northwest", 0);

    add_item(({"crystalline road"}), "The glittering " +
              "crystalline road appears " +
              "to wind its way gradually around the mountain.\n"); 
    add_exit(ROAD+"road10","northwest");
    add_exit(CROAD+"croad0","southeast");
    add_exit(FOOTHILL+"fh23", "northeast");
    add_exit(FOOTHILL+"fh22", "north");
    add_exit(FOOTHILL+"fh34", "west");
    add_exit(FOOTHILL+"fh44", "southwest");
}

