inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Tunnel junction");
    set_long( "You are standing at the intersection of three "+
        "tunnels. North and south runs a large passage, and you could"+
        " probably crawl though a small hole in the east wall.\n" );
 
    add_item("hole", "Peering into the hole you can't make out much. "+
        "Its looks just about large enough to crawl down, but if you were "+
        "attacked.....\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "crawl2","east",0,1);
    add_exit(GRAVEYARD_DIR + "pass1","south",0,1);
    add_exit(GRAVEYARD_DIR + "cave1","north",0,1);
 
}
