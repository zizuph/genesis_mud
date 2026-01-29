
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel hallway, corner");
    set_long("The passageway turns here to branch to the north and east.  To "+
        "the west lies what appears to be a small storage room; you may "+
        "enter it if you please.  North of there, the hall appears to "+
        "split in two.\n");

    AE(RHUN+"citadel/1i","north");
    AE(RHUN+"citadel/1h","west");
    AE(RHUN+"citadel/1f","east");

    add_item(({"walls","stone","wall","stones","arch","arches","ceiling"}),
        "All the walls and ceiling here are made of a smooth black stone, "+
        "obsidian-like in appearance and texture.  The architecture is a "+
        "very old style, with numerous high, curving arches at intervals "+
        "along this very tall and wide hallway.\n");
    add_item(({"hall","hallway","west"}),"The hallway of black stone, "+
        "decorated along its way with numerous curving arches, continues "+
        "to the east and north from here.  It is quite high, probably "+
        "close to six "+
        "or seven meters, as well as wide enough for ten to walk abreast.\n");

    IN;

}

