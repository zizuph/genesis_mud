
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel hallway");
    set_long("You walk through a high, wide hallway of shiny black stone.  "+
        "The architecture here is magnificent-- high, smooth arches and "+
        "tall pillars.  Back to the east, the hall ends in this black "+
        "citadel's entryway, while it continues by curving to the southwest."+
		" A huge archway leads north into what must have been the owner's "+
        "audience chamber or throne room.\n");

    AE(RHUN+"citadel/1e","north");
    AE(RHUN+"citadel/1f","southwest");
    AE(RHUN+"citadel/1b","east");

    add_item(({"walls","stone","wall","stones","arch","arches","ceiling"}),
      "All the walls and ceiling here are made of a smooth black stone, "+
        "obsidian-like in appearance and texture.  The architecture is a "+
        "very old style, with numerous high, curving arches at intervals "+
        "along this very tall and wide hallway.\n");
    add_item(({"hall","hallway","west"}),"The hallway of black stone, "+
        "decorated along its way with numerous curving arches, continues "+
        "to the southwest and east from here.  It is quite high, probably "+
        "close to six "+
        "or seven meters, as well as wide enough for ten to walk abreast.\n");
    add_item(({"north","doorway","chamber","throne room","room",
        "audience chamber"}),"Just north of this entryway, "+
        "through a magnificent arch stretching up perhaps 5 meters" +
        ", stands a great chamber where the noble whose estate this once "+
        "was must have held his court.  You can easily enter it by heading "+
        "in that direction.\n");

    IN;

}

