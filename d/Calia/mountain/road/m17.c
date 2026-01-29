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
    make_the_room("Away to the southeast you can make out an obelisk. To " +
                  "the northeast stands the monument to the fallen.\n", 2);
    add_exit(ROAD+"m12", "north");
    add_exit(ROAD+"m11", "northwest");
    add_exit(ROAD+"m13", "northeast"); 
    add_exit(ROAD+"m18", "east");
    add_exit(ROAD+"m23", "southeast");
}
