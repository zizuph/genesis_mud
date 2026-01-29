/* shirelink */

inherit "/std/room";
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"


create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("The path");
    set_long(BS("You are on the path from the lowlands which goes towards " +
             "Misty mountains. In the eastern direction it climbs up " +
             "into the valley leading to the high pass.\n"));

              /* The other room,           direction, VBFC, fatigue */
//    add_exit("/d/Shire/common/rhovanionlink", "southwest",    0,    1);
    add_exit("/d/Gondor/common/shirelink", "southwest",    0,    1);
    add_exit("/d/Rhovanion/common/misty/p1", "east",    0,    1);

}
