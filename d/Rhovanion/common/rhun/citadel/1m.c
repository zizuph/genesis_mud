
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel hallway, corner");
    set_long("The passageway turns here to branch to the south and east.  To "+
        "the east lies what appears to be a bedchamber; you may "+
        "enter it if you please.  South of there, the hall appears to "+
        "branch off.\n");

    AE(RHUN+"citadel/1n","south");
    AE(RHUN+"citadel/1l","east");

    add_item(({"walls","stone","wall","stones","arch","arches","ceiling"}),
        "All the walls and ceiling here are made of a smooth black stone, "+
        "obsidian-like in appearance and texture.  The architecture is a "+
        "very old style, with numerous high, curving arches at intervals "+
        "along this very tall and wide hallway.\n");
    add_item(({"hall","hallway","west"}),"The hallway of black stone, "+
        "decorated along its way with numerous curving arches, continues "+
        "to the south from here.  It is quite high, probably "+
        "close to six "+
        "or seven meters, as well as wide enough for ten to walk abreast.\n");

    IN;

}

