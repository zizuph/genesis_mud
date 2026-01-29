/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("below rock");
    set_long("You are climbing the slope of Misty Mountains. Above you " +
             "there is a big rock which is exactly in your way upwards. You may " + 
             "pass it to the east or northeast. There is no way to tell which " + 
             "is the right road.\n");


    add_item("rock", "It is big and dark. No way to pass it except " + 
                     "walk around.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p2", "southwest",    0,    4);
    add_exit(MISTY_DIR+"p4", "northeast",    0,    5);
    add_exit(MISTY_DIR+"p18", "east",    0,    10);

}
