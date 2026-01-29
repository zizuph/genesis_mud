#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Lost on a downward path.");
/*
    set_long("You seem to be lost on a downward path. The floor slopes strongly and is covered with slippery rock crystals. There are openings in the walls, but it is so slippery that you neither can walk nor crawl toward them. You simply have to gather speed and hope to end where you want.\n");
*/
    set_long("You are on a downward path. The floor slopes downward " +
        "deeper into the mines and becomes lost in the darkness. It looks " +
        "dangerous with rubble strewn across it from fallen rocks.\n");
    add_item(({"path","floor"}),
	     "It is broken and uneven and covered with fallen rocks.\n");
    add_item(({"broken rocks", "rocks", "rubble"}),
        "They are chunks of rock that has fallen fom the walls and ceiling. " +
        "They are jagged and dangerous looking.\n");
    
/*
    add_exit(THIS_DIR+"sleeping","north","@@my_move");
    add_exit(THIS_DIR+"draglair","south","@@my_move");
    add_exit(THIS_DIR+"knightsh","east","@@my_move");
    add_exit(THIS_DIR+"gallery","west","@@my_move");
    add_exit(THIS_DIR+"vicarage","up","@@my_move");
*/
    add_exit(THIS_DIR+"sleeping","north");
    add_exit(THIS_DIR+"draglair","south");
    add_exit(THIS_DIR+"knightsh","east");
    add_exit(THIS_DIR+"gallery","west");
    add_exit(THIS_DIR+"vicarage","up");

}

int
my_move() {
    int i;
    string *exits;

    exits = query_exit_cmds();
    i = random(sizeof(exits));
    write("You slip on the crystals!!!!!\n");
    write("You slide into one of the openings!\n\n");
    TP->move_living("sliding into a hole", query_exit_rooms()[random(sizeof(exits))]);
    return 1;
}		  
