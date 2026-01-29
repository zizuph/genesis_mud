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
    make_the_room("Away to the southwest you can see a road.\n", 2); 
    add_exit(ROAD+"road13", "southwest");
    add_exit(ROAD+"m16", "north");
    add_exit(ROAD+"m15", "northwest");
    add_exit(ROAD+"m20", "west"); 
    add_exit(ROAD+"m22", "east"); 
    add_exit(ROAD+"m26", "south");
    add_exit(ROAD+"m27", "southeast");
}
