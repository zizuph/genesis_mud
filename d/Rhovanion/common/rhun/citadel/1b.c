
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel entryway");
    set_long("Tall walls of black stone rise up around you as you step "+
        "into the entryway of this forebodingly-dark citadel.  High arches "+
        "curve overhead, perfectly rounded and smooth.  All the walls and "+
        "ceiling here are of that black stone, while the floor is of "+
        "a dark marble.  Every step, every breath echoes here off the "+
        "empty walls, adorned with neither tapestry nor painting, and off "+
        "that marble floor where no rug sits.  A small arched doorway leads "+
        "north from here into a small waiting chamber, while the tall "+
        "hallway continues west.  Tall, heavy doors stand slightly ajar to "+
        "the east, leading back out into the courtyard.\n");

    AE(RHUN+"citadel/1c","north");
    AE(RHUN+"citadel/1d","west");
    AE(RHUN+"citadel/1a","east");

    add_item(({"door","doors","east"}),"The doors to this "+
        "entryway are made of thick wood painted black.  Somehow, that dark "+
        "paint has not faded over time.  They stand slightly ajar-- which is "+
        "a good thing, since they seem much too heavy and the hinges much "+
        "too rusted-- to move.  Through them, to the east, stands this "+
        "dark citadel's courtyard and, beyond it, the outer, eastern gate "+
        "and wall.\n");
    add_item(({"walls","stone","wall","stones","arch","arches","ceiling"}),
        "All the walls and ceiling here are made of a smooth black stone, "+
        "obsidian-like in appearance and texture.  The architecture is a "+
        "very old style, with numerous high, curving arches at intervals "+
        "along this very tall and wide hallway.\n");
    add_item(({"hall","hallway","west"}),"The hallway of black stone, "+
        "decorated along its way with numerous curving arches, continues "+
        "to the west from here.  It is quite high, probably close to six "+
        "or seven meters, as well as wide enough for ten to walk abreast.\n");
    add_item(({"north","doorway","chamber"}),"Just north of this entryway, "+
        "through a low arched doorway of perhaps two meters, stands a small "+
        "waiting chamber, perhaps a place where guests of this citadel's "+
        "owner used to await their invitations into his presence.\n");

    IN;

}

