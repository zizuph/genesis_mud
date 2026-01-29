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
                  "and away to the west you can see a road.\n", 2, 1); 
    add_exit(ROAD+"road12", "west");
    add_exit(ROAD+"road11", "south");
    add_exit(ROAD+"m28", "northeast");
    add_exit(ROAD+"m27", "north");
    add_exit(ROAD+"m26", "northwest");
    add_exit(FOOTHILL+"fh01", "east"); 
    add_exit(ROAD+"m35", "southwest");
    add_exit(FOOTHILL+"fh10", "southeast");
}
