#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("just outside south gate of Altaruk.");
    extra_line("A tall wall surrounds the town as part of its" +
        " defense against frequent attacks by giants.");
    last_line("The road leaves the town gate and goes south into" +
        " the desert. There is a storm raging south of here. You" +
        " better go back into town. Athasian storms are killers.\n");
    
    add_item(({"wall", "town wall"}), "A fifteen-foot stone wall" +
        " rises to the north of you. Despite its heavy defenses," +
        " Altaruk is destroyed on a regular basis by giants from" +
        " the islands of the Forked Tongue Estuary.\n");
        
   add_item("storm", "You can see a dark wall of silt and sand" +
        " not far south from here. It scares you to think what it" +
        " must be like to experience it close up.\n");
        
    add_exit("21", "north", 0,1,0);
}
