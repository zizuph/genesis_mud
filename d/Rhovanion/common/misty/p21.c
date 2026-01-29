/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("grassy path");
    set_long("You are at a grassy path which goes generaly in a east-west "+
             "direction. But you know that only to the east it may lead you "+
             "to places where you can rest a bit.\n");

    add_item("path", "It comes from northwest and goes further east.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p20", "northwest",    0,    4);
    add_exit(MISTY_DIR+"p22", "east",    0,    4);

}
