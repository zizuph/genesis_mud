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
    make_the_room("Away to the northeast you can make out an obelisk, " +
                  "and away to the west you can see a road.\n", 2); 
    add_exit(ROAD+"road15", "west");
    add_exit(ROAD+"road14", "south");
    add_exit(ROAD+"m10", "northeast");
    add_exit(ROAD+"m09", "north");
    add_exit(ROAD+"m08", "northwest");
    add_exit(ROAD+"m15", "east"); 
    add_exit(ROAD+"m19", "southwest");
    add_exit(ROAD+"m20", "southeast");
}
