/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           1.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("Away to the north you can make out an obelisk, " +
                  "and away to the southwest you can see a road.\n", 2); 
    add_exit(ROAD+"road14", "southwest");
    add_exit(ROAD+"m10", "north");
    add_exit(ROAD+"m09", "northwest");
    add_exit(ROAD+"m14", "west"); 
    add_exit(ROAD+"m16", "east"); 
    add_exit(ROAD+"m20", "south");
    add_exit(ROAD+"m21", "southeast");
}
