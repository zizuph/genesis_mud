/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("drowning in the river");
    set_long("You are desperately trying to keep your head above the water "+
             "and not to drown in the swift currents of the River Anduin.\n");

    add_item(({"river","water"}), "The water is icy cold and runs swiftly to "+
                                  "the south.\n");

}
