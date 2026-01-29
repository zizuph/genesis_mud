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
    make_the_room("\n", 2);
    add_exit(ROAD+"m30", "north");
    add_exit(ROAD+"m29", "northwest");
    add_exit(ROAD+"m31", "northeast"); 
    add_exit(ROAD+"m34", "east");
    add_exit(ROAD+"m36", "southeast");
}
