/*
 *  /d/Genesis/start/human/wild2/orc_road2f.c
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
    set_long("You find yourself deep in the Orc Forest, following along " +
        "the flat grey stones of the Orc Road. The snow-capped peaks of " +
        "Grey Mountains reach across the eastern horizon, their rugged " +
        "foothills falling down towards you. Somewhere deep in those " +
        "mountains, the highway runs through the High Pass towards " +
        "the legendary city of Sparkle. Thick bushes and sharp brambles " +
        "surround you here, discouraging anyone from leaving the road to " +
        "explore deeper into the woods. The highway itself cuts through " +
        "the forest, travelling deeper into the forest to the west and " +
        "stretching east towards the mountains.\n");

    add_exit(THIS_DIR + "orc_road3","west");
    add_exit(THIS_DIR + "orc_road2e","east");
    add_exit(THIS_DIR + "orc_road2f", "southeast","@@forest@@",1,1);
    add_exit(THIS_DIR + "orc_road2f", "northeast","@@forest@@",1,1);
    add_exit(THIS_DIR + "orc_road2f", "south","@@forest@@",1,1);
    add_exit(THIS_DIR + "orc_road2f", "north","@@forest@@",1,1);
    add_exit(THIS_DIR + "orc_road2f", "southwest","@@forest@@",1,1);
    add_exit(THIS_DIR + "forest1", "northwest",0,1,1);
    
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

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        forest
 * Description  :        Gives an explanation for why the mortal cannot travel
                         into the forest
 * Returns      :        int 1 - denies moving along the exit path
 */
int
forest()
{
    write("The bushes and brambles are just too thick for you to enter " +
        "the forest from this direction.\n");
    return 1;
}
/* forest */