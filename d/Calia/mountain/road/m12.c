/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           1.5.95          Created                      Maniac
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
    make_the_room("Away to the northeast you can see a road. To the " + 
                  "east stands the monument to the fallen.\n", 2); 
    add_exit(ROAD+"road16", "northeast");
    add_exit(ROAD+"m06", "northwest");
    add_exit(ROAD+"m07", "north");
    add_exit(ROAD+"m11", "west"); 
    add_exit(ROAD+"m13", "east"); 
    add_exit(ROAD+"m17", "south");
    add_exit(ROAD+"m18", "southeast");
    reset_room();
}
