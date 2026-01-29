#include "/d/Rhovanion/defs.h"
inherit "/d/Rhovanion/lib/room";
inherit RHUN_DIR+"tower/inside/guard";
#include <stdproperties.h>

void create_room()
{
    set_short("Dark passage");
    set_long("This dim hallway in the tall, red-bricked"
        +" tower that stands in the midst of the forest in Rhun"
        +" makes a  corner here, turning from east to north.\n");

    add_exit(RHUN_DIR+"tower/inside/1l", "north", 0);
    add_exit(RHUN_DIR+"tower/inside/1j","east",0);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}
