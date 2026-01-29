#include "defs.h"
#include "/sys/terrain.h"

CONSTRUCT_ROOM {

    set_short("An endlessly vast corridor");
    set_long("You are in an endlessly vast corridor that stretches out into " +
        "the darkness to both the east and west. The walls of the tunnel " +
        "are smooth and almost perfectly formed, except for a small niche " +
        "visible in the north wall.\n");
    add_item(({"niche", "gouge"}),
        "There is a small niche in the northern wall " +
        "pierced by a deep gouge. It is almost as if someone broke a " +
        "chunk out of the wall with a mighty swing of an axe.");
    add_item(({"chunk", "chunks"}),
        "You don't see anything like that here.");
    set_no_exit_msg(({"southwest","south","northwest","southeast","north",
            "northeast"}),
        "OOF!\n\nThat wall sure is solid!\n");

    EXIT("corr1", "west");
    EXIT("corr3", "east");
}
