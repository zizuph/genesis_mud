/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           2.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

object rabbit;

void
reset_room()
{
     if (!rabbit) {
          rabbit = clone_object(MOUNTAIN_MONSTERS+"rabbit");
          rabbit->move_living("", this_object());
     }
}


void
create_room()
{
    make_the_room("Away to the east you can make out an obelisk, " +
                  "and to the southwest you can see a road.\n", 2, 1); 

    add_exit(ROAD+"m21", "northwest");
    add_exit(ROAD+"m22", "north");
    add_exit(ROAD+"m26", "west");
    add_exit(ROAD+"m28", "east"); 
    add_exit(ROAD+"m32", "south");
    add_exit(FOOTHILL+"fh01", "southeast");
    add_exit(ROAD+"road12", "southwest");

    reset_room();
}
