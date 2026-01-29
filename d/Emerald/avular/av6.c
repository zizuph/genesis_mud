/*
 * AV6.c
 * Exits underneath the snake bridge to av7
 * - Alaron FEB 2000
 */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit AVULAR_ROOM;


int trap_shout(string str);

void
create_avular_room()
{
    set_short("A city street");
    set_em_long("The narrow, black street descends down a steep slope to the "+
        "south. At the bottom of the slope, an enormous stone-carved bridge arches "+
        "up over the road. The huge bridge is actually an arching, twisting "+
        "sculpture of a giant snake. Small drops of water steadily drip from the underside "+
        "of the stone serpent, forming a large puddle. The veil of engulfing darkness "+
        "obscures the road to the south of the bridge and north of here.\n");

    add_item( ({"puddle", "small puddle", "water", "drops", "drip"}),
             "The water dripping from beneath the serpentine bridge forms "+
             "a puddle at the bottom of the sloping, cobblestoned road. The "+
             "fact that the water does not drain into the soil is a testament "+
             "to the fine, precise construction of the road itself.\n");

    add_item( ({"road", "cobblestone road", "dark road", "dark cobblestone road",
                "stones", "cobblestones", "dark stone", "dark stones"}),
             "The road is formed of thousands of small, dark stones. Each stone "+
             "is individually carved and uniquely shaped, yet the collection of "+
             "all of the stones somehow meshes together to form a narrow road.\n");

    add_item( ({"building", "buildings"}),
        "Several buildings peek out from behind the veil of suffocating blackness surrounding "+
        "this entire area. Each building is completely unique, some of them shaped like domes, "+
        "others traditionally shaped like rectangles or squares.\n");

    add_item( ({"bush", "bushes"}),
        long("grass"));


    add_item( ({"bridge", "snake", "serpent", "sculpture", "serpent bridge",
        "snake bridge" }),
        "The bridge is frightening, disturbing, and a marvel of architecture and design "+
        "all at the same time. The bridge winds from north to south and back again, all "+
        "the while arching upward and then back down. At the east end, it is narrow "+
        "with thousands of small, curved ridges carved into it. At the far west, it "+
        "widens into the form of an enormous snake head, its dark stone fangs sinking "+
        "deep into the cobblestone road beyond. Surveying the awesome site again, you "+
        "notice that the thousands of intricate, unique ridges carved into the stone "+
        "bridge are actually scales carved into the back of this massive, cold stone "+
        "serpent.\n");

    add_exit(AVMAIN+"av5", "north");
    add_exit(AVMAIN+"av7", "south", "@@go_under@@");
}

int
go_under()
{
    tell_room(AVMAIN+"av2",
            "The soft sound of water splashing echoes up from beneath the "+
            "bridge as "+QNAME(this_player())+" walks under the giant snake sculpture, "+
            "heading south.\n");
    return 0;
}

init()
{
    ::init();
    add_action(trap_shout, "shout", 0);
}

int
trap_shout(string str)
{
    if (str == "")
        return 0;

    tell_room(AVMAIN+"av2",
            "From below the bridge, " + QNAME(this_player()) + " shouts: " + str + "\n");
    return 0;
}

