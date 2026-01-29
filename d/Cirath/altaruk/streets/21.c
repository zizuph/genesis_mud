#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("the outskirts of Altaruk.");
    extra_line("A tall wall surrounds the town as part of its" +
        " defense against frequent attacks by giants. People" +
        " are running carrying wares from the caravans.");
    last_line("The road lead south through the gate and into " +
        " the desert.");
    
    add_item(({"wall", "town wall"}), "A fifteen-foot stone wall" +
        " rises to the north of you. Despite its heavy defenses," +
        " Altaruk is destroyed on a regular basis by giants from" +
        " the islands of the Forked Tongue Estuary.\n");    
    
    add_exit("19", "north", 0,1,0);
    add_exit("20", "northeast", 0,1,0);
    add_exit("22", "east", 0,1,0);
    add_exit("23", "south", 0,1,0);
}
