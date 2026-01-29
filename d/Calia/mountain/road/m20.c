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
    make_the_room("Away to the west you can see a road.\n", 2); 
    add_exit(ROAD+"road14", "west");
    add_exit(ROAD+"road13", "south");
    add_exit(ROAD+"m16", "northeast");
    add_exit(ROAD+"m15", "north");
    add_exit(ROAD+"m14", "northwest");
    add_exit(ROAD+"m21", "east"); 
    add_exit(ROAD+"m25", "southwest");
    add_exit(ROAD+"m26", "southeast");

    reset_room();
}
