/*
 *  /d/Genesis/start/human/wild2/orc_road3c.c
 *
 *      Hastily constructed road to assist with making Styles'
 *      maps accurate. (Gorboth)
 *
 * Updated by Varian, March 2016
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
    set_long("You are on the Orc Road, as the road tumbles down towards " +
      "the Orc Forest, just west of the High Pass. Rugged foothills " +
      "surround the edge of the road, with huge boulders and rocks " +
      "resting sitting amongst the wildflowers that grow all over the " +
      "small grassy fields. The highway cuts through a narrow past " +
      "just east of here, while a dark mass of trees huddle around " +
      "the road as it passes further into the western horizon. From " +
      "this elevation, you are just able to make out a small " +
      "cluster of buildings hidden on the northwestern edge of " +
      "the forest below.\n");

    add_exit(THIS_DIR + "orc_road2d","west");
    add_exit(THIS_DIR + "orc_road2b","east","@@pass@@");

    set_no_exit_msg(({"southwest","northwest"}),
        "The bushes and brambles are just too thick for you to enter " +
        "the forest from this direction.\n");
    set_no_exit_msg(({"south","north","northeast","southeast"}),
        "The mountains here look far too difficult for you to climb! You " +
        "will have to find another way around them.\n");

    add_trees(0);

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


/*
 * Function name:        pass
 * Description  :        Provides an echo to tell the player they are climbing
 *                       the High Pass
 * Returns      :        int 0 - allows player to move along the exit path
 */
int
pass()
{
    write("You climb up and over the High Pass.\n");
    return 0;
}
/* pass */