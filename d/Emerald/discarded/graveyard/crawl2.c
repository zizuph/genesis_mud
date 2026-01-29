inherit "/d/Emerald/std/dir_room";
 
#include "/d/Emerald/defs.h"
#define DP(LABEL) ("@@dir_phrase|" + LABEL + "@@")
#define EAST GRAVEYARD_DIR + "crawl1"
#define WEST GRAVEYARD_DIR + "junction"
 
 
void
create_room()
{
    set_short("Widening tunnel");
    set_long( "You are crawling along a narrow tunnel, which seems "+
        "to be sloping "+DP("direction")+" To the west the tunnel can be "+
        "seen to open out enough to stand.\n" );
 
    add_dir_phrase("direction", EAST, "slightly down.");
    add_dir_phrase("direction", WEST, "up.");
    add_dir_phrase("direction", 0, "slightly down.");
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "crawl1","east",0,1);
    add_exit(GRAVEYARD_DIR + "junction","west",0,1);
}
