/*
 * 	orc_road4.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_orcvalley();
    set_items_orcroad();
    set_herbs();

    set_short("Orc road");
    set_long("You are walking along a stone highway, deep inside the lush " +
        "growth of the Orc Forest. Tall trees spring up above the thick " +
        "bushes and sharp brambles which grow near the road, dwarfed only " +
        "by the jagged peaks of the Grey Mountains which seem to cut across " +
        "the horizon in almost every direction. The forest seems very open " +
        "here, with a faint trail wandering north up a slope towards what " +
        "appears to be a fortress barely visible in the distance to the " +
        "northwest. The Orc Road itself runs deeper into the forest to " +
        "the east while nearing the edge of the forest to the west.\n");

    add_exit(THIS_DIR + "slope","north");
    add_exit("/d/Sparkle/area/faerie/rooms/forest/mtroad01", "west");
    add_exit(THIS_DIR + "orc_road3","east");
    add_exit(THIS_DIR + "forest1", "northeast",0,1,1);

    set_no_exit_msg(({"southwest","northwest","south","southeast"}),
        "The bushes and brambles are just too thick for you to enter " +
        "the forest from this direction.\n");

    add_trees(1);

    add_tell("A stiff breeze ripples through the tall trees of the Orc " +
        "Forest.\n");
    add_tell("A partrigde suddenly spreads its wings and flies away " +
        "deeper into the forest.\n");
    add_tell("A twinkling ray of light breaks through the tall trees " +
        "of the Orc Forest.\n");
    add_tell("A brown hare jumps up and crashes away deeper into the " +
        "forest.\n");
    add_tell("Far away from the road, you see a stag jump and bound " +
        "away farther into the woods.\n");
    add_tell("the haunting hooting of an owl echoes in the woods that " +
        "surround you.\n");

    add_item(({"foothill","foothills","rock","rocks","rocky foothill",
            "rocky foothills","rugged foothill","rugged foothills"}),
        "The land both north and south of the road quickly becomes " +
        "rocky and broken as the rugged foothills quickly transform " +
        "themselves into the Grey Mountains.\n");
    add_item(({"trees","tall trees"}),
        "The tall trees of the Orc Forest spread out before you to the " +
        "west, crowding up against the Orc Road as it continues " +
        "on its path towards Faerie. You might even be able to climb " +
        "one of them!\n");
    add_item(({"trail","path","small trail","dirt trail","faint trail",
            "faint dirt trail","small dirt trail"}),
        "Winding off the north side of the highway, a small dirt trail " +
        "is faintly visible, heading off deeper into the woods.\n");
    add_item(({"bushes","bush","bramble","brambles"}),
        "Thick bushes and prickly brambles surround the perimeter of " +
        "the forest, essentially leaving you the choice of simply " +
        "following the road.\n");
    add_item(({"building","cluster","buildings","settlement","fortress"}),
        "The fortress and buildings are not visible from here, but you " +
        "know that they can be found somewhere to the northwest.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}
