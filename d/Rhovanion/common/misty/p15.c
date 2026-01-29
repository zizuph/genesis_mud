/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("west side of ford");
    set_long("You are standing on the western side of the Old Ford through "+
             "the River Anduin. " + 
             "Clear cold water is swiftly running towards the sea somewhere " +
             "far away in the south. It is so shallow here that even you " +
             "may cross it without any difficulties.\n");

    add_item("ford", "You would not find a better place for crossing this " +
                     "river.\n");
    add_item(({"water","river"}), "The water is icy cold. Hope you don't catch " +
                               "a cold while crossing it.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p14", "west",    0,    4);
    add_exit(MISTY_DIR+"p16", "east",    0,    4);

}
