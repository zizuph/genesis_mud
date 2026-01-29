
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel hallway");
    set_long("You stand in a section of the high, dark hallway.  This branch "+
        "heads into a stairwell to the north, and rejoins the main section "+
        "of the passage west of here.\n");

    AE(RHUN+"citadel/1k","north");
    AE(RHUN+"citadel/1i","west");

    add_item(({"walls","stone","wall","stones","arch","arches","ceiling"}),
        "All the walls and ceiling here are made of a smooth black stone, "+
        "obsidian-like in appearance and texture.  The architecture is a "+
        "very old style, with numerous high, curving arches at intervals "+
        "along this very tall and wide hallway.\n");
    add_item(({"hall","hallway","west"}),"The hallway of black stone, "+
        "decorated along its way with numerous curving arches, continues "+
        "to the west and north from here.  It is quite high, probably "+
        "close to six "+
        "or seven meters, as well as wide enough for ten to walk abreast.\n");

    IN;

}

