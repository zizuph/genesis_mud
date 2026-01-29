#include "defs.h"

CONSTRUCT_ROOM {
    set_short("An oval room.");
    set_long("An oval room. You smell some sulfide here.\n");
    add_item(({"sulfide","sulfides"}),"Yack! It is by no means a nice smell.");
    add_neg(({"smell", "sniff", "inhale"}),
        "[the] 'air' / 'smell' / 'scent' / 'sulfide' [in] [the] [air] [room]",
        "Yack! It smells terribly!\n");
    EXIT("suddenst","up");
    EXIT("big_hall","west");
}
