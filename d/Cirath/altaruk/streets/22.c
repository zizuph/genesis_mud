#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("the outskirts of Altaruk.");
    extra_line("A tall wall surrounds the town as part of its" +
        " defense against frequent attacks by giants. People" +
        " are running carrying wares from the caravans.");
    last_line("The caravan office lies east of here. There is" +
        " a caravan here.");
    
    add_item(({"wall", "town wall"}), "A fifteen-foot stone wall" +
        " rises to the north of you. Despite its heavy defenses," +
        " Altaruk is destroyed on a regular basis by giants from" +
        " the islands of the Forked Tongue Estuary.\n");
        
    add_item("caravan", "The is about twenty Erdlus packed with" +
        " wares and elven riders on Erdlus to guard it. They are" +
        " waiting for the weather to get better so they can set" +
        " out on the road to Balic.\n");
    
    add_item(({"office", "caravan office"}), "The caravan office" +
        " keeps track of all the caravans going through Altaruk" +
        " and caravans from rival merchant houses must pay toll" +
        " here. They also hire people to work on the caravans" +
        " from time to time.\n");
    
    add_exit(ALT_HOU + "caro", "east", 0,1,0);
    add_exit("19", "northwest", 0,1,0);
    add_exit("20", "north", 0,1,0);
    add_exit("21", "west", 0,1,0);
}
