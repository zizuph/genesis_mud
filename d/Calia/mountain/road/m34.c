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
    make_the_room("Away to the northeast you can see a road.\n", 2, 1); 
    add_exit(ROAD+"road12", "northeast");
    add_exit(ROAD+"m30", "northwest");
    add_exit(ROAD+"m31", "north");
    add_exit(ROAD+"m33", "west"); 
    add_exit(ROAD+"m35", "east"); 
    add_exit(ROAD+"m36", "south");
    add_exit(FOOTHILL+"fh19", "southeast");
}
