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
    make_the_room("Away to the east you can see a road. To the southeast " +
                  "stands the monument to the fallen.\n", 2); 
    add_exit(ROAD+"road16", "east");
    add_exit(ROAD+"road17", "north");
    add_exit(ROAD+"m01", "northwest");
    add_exit(ROAD+"m02", "northeast");
    add_exit(ROAD+"m06", "west"); 
    add_exit(ROAD+"m11", "southwest");
    add_exit(ROAD+"m12", "south");
    add_exit(ROAD+"m13", "southeast");
}
