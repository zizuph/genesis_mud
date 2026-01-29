#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_walkway();
    
    add_exit("m1_00", "west");
    add_exit("m1_20", "east");
    add_exit("m1_11", "north");
    add_exit("m1_01", "northwest");
    add_exit("m1_21", "northeast");
}
