/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("at slope");
    set_long("You are climbing the slope of the Misty Mountains. Above you " + 
             "can see the top of it.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p8", "southwest",    0,    10);
    add_exit(MISTY_DIR+"p10", "southeast",    0,    10);

}
