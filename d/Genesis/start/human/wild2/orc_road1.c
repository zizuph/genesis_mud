/* 	
 * orc_road1.c			Styles.   3 Mar 1993
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
    set_items_sparkle();
    set_items_orcroad();
    set_herbs();

    set_short("Orc road");
    set_long("You are walking along a long, straight highway that runs " +
        "directly west out of the city of Sparkle before it climbs up to " +
        "the top of the high pass that splits the Grey Mountains. The " +
        "highway has been dubbed the Orc Road, in honour of the traditional " +
        "homelands of the orcs which lay beyond the pass. Scattered trees " +
        "and fields surround the road here with rolling foothills beginning " +
        "to rise just west of here. Immediately to the east, you can see a " +
        "busy crossroads and the walls of Sparkle standing just beyond. " +
        "To the south, a narrow dirt lane winds away from the flat stones " +
        "of the road, winding up through the flowers to the top of a grassy " +
        "hill.\n");

    add_trees(0);         

    add_exit(THIS_DIR + "orc_road2","west");
    add_exit(THIS_DIR + "lane","south");
    add_exit(THIS_DIR + "crossroad","east");
    add_exit(THIS_DIR + "s_road1a", "southeast", 0,1,1);
    add_exit(THIS_DIR + "n_road1", "northeast",0,1,1);

    set_no_exit_msg(({"north","northwest"}),
        "In order to go in that direction, you would need to have the " +
        "skills of an expert mountain climber. It looks like you will have " +
        "to go in another direction for now.\n");
    set_no_exit_msg(({"southwest"}),
        "The hill looks a little bit too difficult to climb in that " +
        "direction, perhaps you should use the path south instead?\n");

    add_item(({"here"}),
        "You are walking along a long, straight highway that runs " +
        "directly west out of the city of Sparkle before it climbs up to " +
        "the top of the high pass that splits the Grey Mountains. The " +
        "highway has been dubbed the Orc Road, in honour of the traditional " +
        "homelands of the orcs which lay beyond the pass. Scattered trees " +
        "and fields surround the road here with rolling foothills beginning " +
        "to rise just west of here. Immediately to the east, you can see a " +
        "busy crossroads and the walls of Sparkle standing just beyond. " +
        "To the south, a narrow dirt lane winds away from the flat stones " +
        "of the road, winding up through the flowers to the top of a grassy " +
        "hill.\n");
    add_item(({"lane", "path", "dirt", "dirt lane", "narrow lane"}),
        "This narrow lane is made of dirt and leads south from the " +
        "Orc Road up to the top of a tall grassy hill. On either " +
        "side of the path, two long rows of small yellow flowers " +
        "follow the lane to the top of the hill.\n");
    add_item(({"hill", "grassy hill", "small hill"}),
        "Rising up to the southwest, you see a small grassy hill which " +
        "seems to gaze out across the valley. You also notice a small dirt " +
        "lane, bordered in twin rows of yellow flowers, which winds its " +
        "way up to the top.\n");
    add_item(({"yellow flowers","flower","flowers","wildflower",
            "wildflowers","row","rows"}),
        "Hugging the edges of the lane to the south are twin rows of " +
        "yellow flowers that wind up to the top of the hill. While dotting " +
        "the fields of grass around the valley, with a colourful splash of " +
        "whimsy, are dozens of different varieties of wildflower. They " +
        "seem to bloom in almost every colour, attracting a collection of " +
        "bees and other various insects.\n");
    add_item(({"spur","mountain spur"}),
        "A rugged spur of mountains cuts through the valley just north " +
        "of the road, making passage in that direction impossible.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}