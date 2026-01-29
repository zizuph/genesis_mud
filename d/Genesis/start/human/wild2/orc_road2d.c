/*
 *  /d/Genesis/start/human/wild2/orc_road2d.c
 *
 *      Hastily constructed road to assist with making Styles'
 *      maps accurate. (Gorboth)
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
    set_long("You are walking along the Orc Road right where it meets the " +
        "eastern edge of the Orc Forest. To the east, the jagged peaks of " +
        "the Grey Mountains are outlined high upon the horizon, broken " +
        "only where the road climbs up the rugged foothills to cut through " +
        "the High Pass. To the west, the highway slices through the dark " +
        "shadows of the woods which loom over the thick bushes and sharp " +
        "brambles that do their best to keep intruders out. Deeper in the " +
        "forest to the northwest, there appears to a small cluster of " +
        "buildings huddled around a primitive looking fortress.\n");

    add_exit(THIS_DIR + "orc_road2e","west");
    add_exit(THIS_DIR + "orc_road2c","east");

    set_no_exit_msg(({"southwest","northwest","north","south"}),
        "The bushes and brambles are just too thick for you to enter " +
        "the forest from this direction.\n");
    set_no_exit_msg(({"northeast","southeast"}),
        "The mountains here look far too difficult for you to climb! You " +
        "will have to find another way around them.\n");
    
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
    add_item(({"bushes","bush","bramble","brambles"}),
        "Thick bushes and prickly brambles surround the perimeter of " +
        "the forest, essentially leaving you the choice of simply " +
        "following the road.\n");
    add_item(({"building","cluster","buildings","settlement","fortress"}),
        "The fortress and buildings are not visible from here, but you " +
        "know that they can be found somewhere to the northwest.\n");

    add_item(({"foothill","foothills","rock","rocks","rocky foothill",
            "rocky foothills","rugged foothill","rugged foothills"}),
        "The land both north and south of the road quickly becomes " +
        "rocky and broken as the rugged foothills quickly transform " +
        "themselves into the Grey Mountains.\n");
    add_item(({"trees","tall trees"}),
        "The tall trees of the Orc Forest spread out before you to the " +
        "west, crowding up against the Orc Road as it continues " +
        "on its path towards Faerie.\n");
    add_item(({"bushes","bush","bramble","brambles"}),
        "Thick bushes and prickly brambles surround the perimeter of " +
        "the forest, essentially leaving you the choice of simply " +
        "following the road.\n");
    add_item(({"building","cluster","buildings","settlement","fortress"}),
        "Barely visible in the distance, you are just able to make out " +
        "a cluster of tiny buildings around a larger fortress. This " +
        "appears to be a orc settlement of sorts.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}
