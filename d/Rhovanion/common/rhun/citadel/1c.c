
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Waiting room");
    set_long("This is a small waiting room in this dark citadel.  Like the "+
        "rest of this estate, the walls and ceiling are all made from smooth "+
        "black stone and are unadorned.  The floor here is dark marble.  "+
        "The only exit from this room is a low arched doorway leading "+
        "south.\n");

    AE(RHUN+"citadel/1b","south");

    add_item(({"walls","stone","wall","stones","arch","arches","ceiling"}),
        "All the walls and ceiling are made of a smooth black stone, "+
        "obsidian-like in appearance and texture.  The architecture is a "+
        "very old style, you surmise.\n");
    add_item(({"south","doorway","chamber"}),"Just south of this room, "+
        "through a low arched doorway of perhaps two meters, stands a grand "+
        "entryway, just beside the main doors of this estate.\n");

    IN;

}

