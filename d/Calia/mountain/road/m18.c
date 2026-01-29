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
    make_the_room("Away to the south you can make out an obelisk, and " +
                  "away to the northeast you can see a road. To the " +
                  "north stands the monument to the fallen.\n", 2); 
    add_exit(ROAD+"road15", "northeast");
    add_exit(ROAD+"m12", "northwest");
    add_exit(ROAD+"m13", "north");
    add_exit(ROAD+"m17", "west"); 
    add_exit(ROAD+"m19", "east"); 
    add_exit(ROAD+"m23", "south");
    add_exit(ROAD+"m24", "southeast");
}
