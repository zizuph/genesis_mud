#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

#include "../defs.h"

inherit "/std/room";

void
create_room()
{
    set_short("The harbour");
    set_long("\n"+
             "You are swimming in the harbour!\n"+
             "Pieces of fish in the water and leftovers from the fishermens'\n"+
             "work, have the sea birds flying around your head. This soup of\n"+
             "guts and gore isn't very pleasant to swim around in.\n"+
             "");

    add_item(({"harbour" }),"It's full of water, seagulls, pieces of fish, and you.\n"+
    "");
    add_item(({"fish","guts","gore" }),"It smells like... Yuck!\n"+
    "");
    add_item(({"birds","seagulls" }),"They're a real nuisance.\n"+
    "");
    add_item(({"water" }),"It's rather filthy. In other words, so are you.\n"+
    "");

    add_exit(TOWN_DIR + "harbour","north");
    add_exit(TOWN_DIR + "sea2","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
