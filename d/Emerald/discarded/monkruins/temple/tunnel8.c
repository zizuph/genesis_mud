inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Escape tunnel");
    set_long("   It's dark except for a dim light west of "+
             "you. The tunnel continues north and west.\n\n");

    add_item("ground","It's soft.\n");

    add_exit(TEMPLE_DIR + "tunnel7", "north", 0);
    add_exit(TEMPLE_DIR + "tunnel9", "west", 0);
}
