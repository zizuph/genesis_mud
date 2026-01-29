#pragma strict_types

#include "../defs.h"

inherit (MORDOR_LIB + "room");

public void
create_room()
{
    set_short("At the pass of Carach Angren."); 

    set_long("The broad paved road stretches southeastwards towards " +
     "the gates of Carach Angren and northwestwards into the circular " +
     "valley of Udun. The heavily contruction of the second gate leading " +
     "into Mordor stands firmly betveen the enclosement of Ephel Duath and " +
     "Ered Lithui.\n");

    add_exit(ROOM + "gor11", "northwest");
    add_exit(ROOM + "gor13", "southeast");
}
