inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
    set_short("Dark passage");
    set_long("This dim hallway in the tall, red-bricked"
        +" tower that stands in the midst of the forest in Rhun"
        +" makes a sharp corner here, turning from northeast to north."
        +"  There is also an exit back out into the clearing to the"
        +" south.\n");

    add_exit(RHUN_DIR+"tower/inside/1h", "north", 0);
    add_exit(RHUN_DIR+"tower/clearing/cl3", "south", 0);
    add_exit(RHUN_DIR+"tower/inside/1f","northeast",0);

    add_prop(ROOM_I_INSIDE, 1);
}

