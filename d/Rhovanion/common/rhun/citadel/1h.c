
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Storage room");
    set_long("This small room is much like the rest of the citadel, though "+
        "much less impressive.  It appears to have been used just for "+
        "storage of necessary goods.  Now, is is empty, and, for the most "+
        "part, uninteresting.  Its only exit lies back to the east into the "+
        "grand hallway.\n");

    AE(RHUN+"citadel/1g","east");

    add_item(({"walls","stone","wall","stones","arch","arches","ceiling"}),
        "All the walls and ceiling are made of a smooth black stone, "+
        "obsidian-like in appearance and texture.  The architecture is a "+
        "very old style, you surmise.\n");
    add_item(({"east","hall","hallway"}),"Just east of this room, "+
        "stands the great hallway, turning from east to north.\n");

    IN;

}

