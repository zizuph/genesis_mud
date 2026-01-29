/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           2.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

object cow;

void
reset_room()
{
     if (!cow) {
          cow = clone_object(MOUNTAIN_MONSTERS+"cow");
          cow->move_living("", this_object());
     }
}


void
create_room()
{
    make_the_room("\n", 2, 1); 
    add_exit(ROAD+"m33", "northwest");
    add_exit(ROAD+"m34", "north");
    add_exit(ROAD+"m35", "northeast");
    add_exit(FOOTHILL+"fh19", "east");
    add_exit(FOOTHILL+"fh32", "southeast");
    add_exit(FOOTHILL+"fh31", "south");

    reset_room();
}
