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
    make_the_room("Away to the west you can see a road.\n", 2);   
    add_exit(ROAD+"road18", "northwest");
    add_exit(ROAD+"road17", "west");
    add_exit(ROAD+"road16", "south");
    add_exit(ROAD+"m03", "east");
    add_exit(ROAD+"m08", "southeast"); 
    add_exit(ROAD+"m07", "southwest");
}
