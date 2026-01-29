// Sea in the underground ocean.
//   -Ilyian, 1995
inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("dark sea near a landing");
    set_long("The black water around ripples with "
            +"fearful currents. To the north a landing "
            +"from a large island extends out over "
            +"the water. The island looms before you "
            +"like a bad dream, threatening of "
            +"a strange and terrible fate.\n");
    AI(({"island","islands"}),"The island is covered "
            +"in a thick mist that seems to "
            +"enshroud everything. In the center of the "
            +"island you think you can make out a large "
            +"hill jutting out of the fog.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
