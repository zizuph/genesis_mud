/* Moorland in the mid-west of Calia.

   Coded by Maniac.

   History: 
           28.4.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include "/d/Calia/mountain/defs.h"

void
create_room()
{
    make_the_room("Away to the southwest you can see a road.\n", 2);   
    add_exit(ROAD+"road16", "southwest");
    add_exit(ROAD+"m02", "west");
    add_exit(ROAD+"m04", "east");
    add_exit(ROAD+"m08", "south"); 
    add_exit(ROAD+"m09", "southeast");
}
