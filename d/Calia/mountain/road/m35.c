/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           2.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"


void
create_room()
{
    make_the_room("Away to the east you can see a road.\n", 2, 1); 
    add_exit(ROAD+"road11", "east");
    add_exit(ROAD+"road12", "north");
    add_exit(ROAD+"m31", "northwest");
    add_exit(ROAD+"m32", "northeast");
    add_exit(ROAD+"m34", "west"); 
    add_exit(ROAD+"m36", "southwest");
    add_exit(FOOTHILL+"fh19", "south");
    add_exit(FOOTHILL+"fh20", "southeast");
}
