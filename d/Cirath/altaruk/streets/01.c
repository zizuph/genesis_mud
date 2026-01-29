#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("just outside north gate of Altaruk.");
    extra_line("A tall wall surrounds the town as part of its" +
        " defense against frequent attacks by giants.");
    last_line("The road leaves the town gate and goes" +
        " north into the desert.");
    
    add_item(({"wall", "town wall"}), "A fifteen-foot stone wall" +
        " rises to the north of you. Despite its heavy defenses," +
        " Altaruk is destroyed on a regular basis by giants from" +
        " the islands of the Forked Tongue Estuary.\n");
    
    add_exit("??", "north", 0,1,0);
    add_exit("02", "south", 0,1,0);
}
