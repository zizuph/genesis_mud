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
    make_the_room("Away to the east you can see a road.\n", 2); 
    add_exit(ROAD+"road12", "east");
    add_exit(ROAD+"road13", "north");
    add_exit(ROAD+"m25", "northwest");
    add_exit(ROAD+"m26", "northeast");
    add_exit(ROAD+"m30", "west"); 
    add_exit(ROAD+"m33", "southwest");
    add_exit(ROAD+"m34", "south");
    add_exit(ROAD+"m35", "southeast");
}
