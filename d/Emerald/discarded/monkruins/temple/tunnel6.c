inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Escape tunnel");
    set_long("   The tunnel continues east and west.\n\n");

    add_item("ground","It's soft.\n");

    add_exit(TEMPLE_DIR + "tunnel5", "east", 0);
    add_exit(TEMPLE_DIR + "tunnel7", "west", 0);
}
