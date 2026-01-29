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
    make_the_room("Away to the west you can see a road. To the southwest " +
                  "stands the monument to the fallen.\n", 2); 
    add_exit(ROAD+"road16", "west");
    add_exit(ROAD+"road15", "south");
    add_exit(ROAD+"m04", "northeast");
    add_exit(ROAD+"m03", "north");
    add_exit(ROAD+"m02", "northwest");
    add_exit(ROAD+"m09", "east"); 
    add_exit(ROAD+"m13", "southwest");
    add_exit(ROAD+"m14", "southeast");
}
