#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Hallway");
    set_long("Hallway\n");
    
    add_exit("m3_30", "west");
    add_exit("m3_50", "east");
    add_exit("m3_41", "north");
}
