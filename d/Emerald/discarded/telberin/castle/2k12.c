#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Courtyard balcony");
    set_long("this is a room overlooking the courtyard...outside. "+
             "describe me now!\n");

    add_exit(CASTLE_DIR + "th2", "south");
}
