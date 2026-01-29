/* Clock room in the crystalline palace.

   Coded by Glykron. 

   History:
           6/4/96     tidied up kroug handling         Maniac
           22/9/95  kroug raid code installed              Maniac        
*/

#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include "defs.h"


void
create_room()
{
    set_short("The clock room");
    set_long(break_string(
        "This is a large trapezoidal-shaped room whose north and south walls " +
        "slope away from you to the west.  " +
        "There is a bed up against the west wall, and a huge clock above the " +
        "bed.  " +
        "\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("light_training"), "east", 0);
    add_exit(ROOM("light_good"), "north", 0);
    add_exit(ROOM("light_bank"), "south", 0);
    add_item("bed", "The bed seems to be still neatly made.\n");
    add_item("clock", "It seems to be very late at night.\n");
}
