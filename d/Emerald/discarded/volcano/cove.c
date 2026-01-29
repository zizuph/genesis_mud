inherit "/std/room.c";
#include "tdefs.h"

create_room()
{
   set_short("Cove");
   set_long("   You are standing in a cove north of the docks. The "+
        "water is a deep blue and the surf is rolling in "+
        "with a gentle rumbling sound. The sand feels warm and "+
        "welcoming under your feet as the seagulls soar above you and "+
        "dart around in search of food. You think you can make out a "+
        "cave in the rock wall at the edge of the beach.\n\n");
    
    add_item(({"docks", "pier"}), "Looking south you can see the docks "+
        "where the ships land.\n");
    add_item(({"water", "sea", "ocean"}), "The water is deep and "+
        "blue beyond the surf. In the distance you can make out what "+
        "looks to be an island.\n");
    add_item(({"surf", "waves"}), "The waves roll in and pound upon the "+
        "sand of the beach.\n");
    add_item(({"sand", "beach"}), "The sand is a dark rich colour where "+
        "the waves have washed over it.\n");
    add_item(({"seagulls", "birds"}), "The seagulls fly above you in "+
        "graceful patterns, occasionally darting to the surface of the "+
        "water to snatch up a fish.\n");
    add_item(({"cave", "wall", "rock wall", "edge"}), "Looking more "+
        "closely you are sure that you can enter a cave on the edge of "+
        "the beach. The entrance is dark and you cannot see inside.\n");
    add_exit(VOL + "pier2", "south");
   
}
