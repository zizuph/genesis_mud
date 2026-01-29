#include "../defs.h"
inherit "/d/Cirath/std/room.c";
#include <macros.h>

void
create_room()
{
    set_short("test room.");
    set_long("This is  a test room. There is a hole in the ground.\n");

    add_item("hole","There is a hole in ground.\n");
    
    add_exit(ALT_STR + "25.c", "north", 0, 1, 0);
}
