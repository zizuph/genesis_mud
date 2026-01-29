/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("above rock");
    set_long("You are climbing the slope of Misty Mountains. Below you " +
             "there is a big rock which is exactly in your way down. You " + 
             "may pass it to the south or southwest. There is no way to " +  
             "tell which is the right road.\n");


    add_item("rock", "It is big and dark. No way to pass it except " + 
                     "walk around.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p5", "east",    0,    8);
    add_exit(MISTY_DIR+"p3", "southwest",    0,    5);
    add_exit(MISTY_DIR+"p18", "south",     0, 10);

}
