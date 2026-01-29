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
    make_the_room("Away to the southwest you can make out an obelisk, " +
               "and away to the east you can see a road. To the northwest " +
               "stands the monument to the fallen.\n", 2); 
    add_exit(ROAD+"road14", "east");
    add_exit(ROAD+"road15", "north");
    add_exit(ROAD+"m13", "northwest");
    add_exit(ROAD+"m14", "northeast");
    add_exit(ROAD+"m18", "west"); 
    add_exit(ROAD+"m23", "southwest");
    add_exit(ROAD+"m24", "south");
    add_exit(ROAD+"m25", "southeast");
}
