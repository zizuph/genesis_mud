/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           1.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

object q_wolf;

void
reset_room()
{
     if (!q_wolf) {
          q_wolf = clone_object(MOUNTAIN_MONSTERS+"q_wolf");
          q_wolf->move_living("", this_object());
     }
}


void
create_room()
{
    make_the_room("Away to the northeast you can see a road.\n", 2); 
    add_exit(ROAD+"road13", "northeast");
    add_exit(ROAD+"m24", "northwest");
    add_exit(ROAD+"m25", "north");
    add_exit(ROAD+"m29", "west"); 
    add_exit(ROAD+"m31", "east"); 
    add_exit(ROAD+"m33", "south");
    add_exit(ROAD+"m34", "southeast");

    reset_room();
}
