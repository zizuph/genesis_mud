#include "/d/Rhovanion/defs.h"
inherit "/d/Rhovanion/lib/room";
inherit RHUN_DIR+"tower/inside/guard";
#include <stdproperties.h>

void create_room()
{
    set_short("Dark passage");
    set_long("This dim hallway in the tall, red-bricked"
        +" tower that stands in the midst of the forest in Rhun"
        +" makes a sharp corner here, turning from east to southeast."
        +"  You might also step out onto the stone balcony which surrounds"
        +" the tower at its second level, just to the north.\n");

    add_exit(RHUN_DIR+"tower/inside/2d","east",0);
    add_exit(RHUN_DIR+"tower/inside/2b", "southeast", 0);
    add_exit(RHUN_DIR+"tower/inside/2balcony7", "north", 0);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}
