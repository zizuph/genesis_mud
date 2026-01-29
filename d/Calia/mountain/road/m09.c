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
    make_the_room("Away to the east you can make out an obelisk, " +
                  "and to the southwest you can see a road.\n", 2); 
     
    add_exit(ROAD+"m03", "northwest");
    add_exit(ROAD+"m04", "north");
    add_exit(ROAD+"m08", "west");
    add_exit(ROAD+"m10", "east"); 
    add_exit(ROAD+"m14", "south");
    add_exit(ROAD+"m15", "southeast");
    add_exit(ROAD+"road15", "southwest");
}
