
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
	reset_euid();

    if(!find_living("_citadel_guard_1i"))
    {
        object guard;
		guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_1i");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Citadel hallway, split");
    set_long("You walk through a huge and magnificent hallway of black "+
        "stone, marked by high and beautiful arches, though no painting "+
        "or tapestry adorns the walls.  The hall splits here, leading off "+
        "to the north, south and east.\n");

    AE(RHUN+"citadel/1n","north");
    AE(RHUN+"citadel/1g","south");
    AE(RHUN+"citadel/1j","east");

    add_item(({"walls","stone","wall","stones","arch","arches","ceiling"}),
        "All the walls and ceiling here are made of a smooth black stone, "+
        "obsidian-like in appearance and texture.  The architecture is a "+
        "very old style, with numerous high, curving arches at intervals "+
        "along this very tall and wide hallway.\n");
    add_item(({"hall","hallway","west"}),"The hallway of black stone, "+
        "decorated along its way with numerous curving arches, continues "+
        "to the east, south and north from here.  It is quite high, probably "+
        "close to six "+
        "or seven meters, as well as wide enough for ten to walk abreast.\n");

    IN;

    reset_room();

}

