#include "local.h"

inherit BARRACK_BASE;

// Prototypes
int block();

void
create_barrack()
{
    add_exit(ROOM_DIR + "barrack_2_11", "north");
    add_exit(ROOM_DIR + "street_3_12", "east");
    add_exit(ROOM_DIR + "barrack_2_13", "south");
    // Make the exit go to this room since we don't have 
    // one for this gate to actually exit to.
    add_exit(ROOM_DIR + "barrack_2_12", "west", block);
}

int
block()
{
    write("The gates are firmly shut, preventing you from "+
      "heading "+query_verb()+".\n");
    return 1;
}
