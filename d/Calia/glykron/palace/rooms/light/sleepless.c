/* Sleepless room in the crystalline palace.

   Coded by Glykron.

   History:
           6/4/96     tidied up kroug handling         Maniac
           22/9/95      Kroug raid code installed             Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";

#include <stdproperties.h>
#include "defs.h"


void
create_room()
{
    set_short("The sleepless room");
    set_long(
        "This is a small trapezoidal-shaped room whose north and west walls " +
	"slope away from you to the northeast.  " +
	"You see an unmade bed in the corner.  " +
	"\n"
    );
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("light_hardware_shop"), "south", 0);
    add_exit(ROOM("light_bronze"), "southwest", 0);
    add_item("bed", "It looks like someone had a sleepless night.\n");
}
