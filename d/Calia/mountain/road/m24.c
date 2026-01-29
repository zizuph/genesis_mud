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
    make_the_room("Away to the west you can make out an obelisk, " +
                  "and away to the northeast you can see a road.\n", 2);   
    add_exit(ROAD+"road14", "northeast");
    add_exit(ROAD+"m19", "north");
    add_exit(ROAD+"m18", "northwest");
    add_exit(ROAD+"m23", "west");
    add_exit(ROAD+"m25", "east"); 
    add_exit(ROAD+"m29", "south");
    add_exit(ROAD+"m30", "southeast");
}
