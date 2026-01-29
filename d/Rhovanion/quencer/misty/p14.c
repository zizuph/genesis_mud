/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("path");
    set_long("You are on nice grassy path. To the west you can see " + 
             "the huge peaks of Misty Mountains. To the east you see " +
             "some river far away.\n");

    add_item(({"peak","peaks","mountains"}), "The peaks are high and dark.\n");
    add_item("river", "Hmmmm... It must be the river Anduin.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p13", "west",    0,    6);
    add_exit(MISTY_DIR+"p15", "east",    0,    4);

}
