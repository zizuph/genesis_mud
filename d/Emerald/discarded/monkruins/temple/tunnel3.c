inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Escape tunnel");
    set_long("   The tunnel continues east and south.\n\n");

    add_item("ground","It's soft.\n");

    add_exit(TEMPLE_DIR + "tunnel2", "south", 0);
    add_exit(TEMPLE_DIR + "tunnel4", "east", 0);
}
