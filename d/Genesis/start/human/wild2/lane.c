/*
 * 	lane.c			Styles.   3 Mar 1993
 *
 *  Modified by Varian, October 2015
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
    set_herbs();

    set_short("A lane leading to the top of a hill");
    set_long("You on a narrow dirt lane which has branched off south from " +
        "the Orc Road and seems to be leading up to the top of a tall grassy " +
        "hill. Off in the far distance to the east, you think you can make " +
        "out the town of Sparkle as it sits on the wide blue waters of the " +
        "Pen Sea. In almost every other direction, the snow-capped peaks " +
        "of the majestic Grey Mountains dominates your view, their jagged " +
        "heights piercing the sky above. Rows of small yellow flowers " +
        "line the edge of the lane, escorting it as it cuts a path " +
        "through the green grass up to the top of the hill.\n");

    add_trees(0);

    add_exit(THIS_DIR + "orc_road1","north");
    add_exit(THIS_DIR + "mansion","west");

    set_no_exit_msg(({"southwest","south"}),
        "It looks like it would be a little difficult doing off in that " +
        "direction from here, it might be better to stick to the path you " +
        "are on.\n");
    set_no_exit_msg(({"east","southeast","northwest","northeast"}),
        "The hill looks a little bit steep in that direction, you " +
        "can follow the path east to get back to the Orc Road.\n");


    add_item(({"here"}),
        "You on a narrow dirt lane which has branched off south from " +
        "the Orc Road and seems to be leading up to the top of a tall grassy " +
        "hill. Off in the far distance to the east, you think you can make " +
        "out the town of Sparkle as it sits on the wide blue waters of the " +
        "Pen Sea. In almost every other direction, the snow-capped peaks " +
        "of the majestic Grey Mountains dominates your view, their jagged " +
        "heights piercing the sky above. Rows of small yellow flowers " +
        "line the edge of the lane, escorting it as it cuts a path " +
        "through the green grass up to the top of the hill.\n");
    add_item(({"mountain", "mountains", "grey mountains", "peak", "peaks"}),
        "Stretching across most of the horizon, you see an endless " +
        "line of jagged, snow-capped mountain peaks as they pierce the " +
        "sky. These are the Grey Mountains, a legendary fixture in the " +
        "countryside surrounding Sparkle. It is said that the " +
        "traditional homeland of the dwarves, Dwarfheim is hidden " +
        "somewhere to the north, while somewhere in the south, goblins " +
        "have tunneled deep into the heart of the mountains, " +
        "establishing a realm of their own.\n");
    add_item(({"sea", "pen sea", "waters", "water"}),
        "Spreading out to the east, farther than the eye can see, is " +
        "the Pen Sea. Nearby, to the east, you can see the famous " +
        "port of Sparkle, a major hub of activity with a constant " +
        "stream of ships arriving and departing from even the most " +
        "remote corners of the world.\n");
    add_item(({"crossroads", "crossroad"}),
        "The Orc Road run east to intersect with a wide and busy road " +
        "which seems to run both north and south. However, it is " +
        "difficult to tell, as the roads seem to get lost behind the " +
        "Grey Mountains which dominate the horizon in almost every " +
        "direction.\n");
    add_item(({"sparkle", "town", "city", "village", "port"}),
        "To the east, you can just barely see the town of " +
        "Sparkle, the legendary port city which is the hub of the " +
        "Pen Sea. The town appears to be quite lively, as if it " +
        "never sleeps, a feeling which is only accented by the fact " +
        "that there appears to be an endless stream of ships which " +
        "are either arriving or departing from the great port.\n");
    add_item(({"flower", "flowers", "yellow flower", "yellow flowers",
                "row", "rows", "small flower", "small flowers"}),
        "Dozens of small yellow flowers are lined up in two rows, " +
        "escorting the lane as it winds its way up the grassy hill. " +
        "The flowers appear to be in full bloom, their sweet scent " +
        "filling the air. Beyond the lane, dozens of colourful " +
        "wildflowers have been sprinkled across the fields.\n");
    add_item(({"lane", "path", "dirt", "dirt lane", "narrow lane"}),
        "This narrow lane is made of dirt and leads south from the " +
        "Orc Road up to the top of a tall grassy hill. On either " +
        "side of the path, two long rows of small yellow flowers " +
        "follow the lane to the top of the hill.\n");
    add_item(({"road", "orc road"}),
        "Just to the north, you can see the lane you are on join " +
        "up with the wide dusty path of the Orc Road. Leading from " +
        "the town of Sparkle and digging passage through a high " +
        "pass, the Orc Road continues west towards the Orc Forest " +
        "before turning south as the road to Faerie.\n");
    add_item(({"hill", "grassy hill", "tall hill", "top", "hilltop"}),
        "This tall hill is covered in a carpet of dark green grass. " +
        "The dirt lane you are on winds up to the top of the hill, " +
        "despite the fact that there does not appear to be anything " +
        "of interest there.\n");
    add_item(({"green oaks", "faerie", "greenoaks"}),
        "The village of Green Oaks, in the land of Faerie, sits " +
        "far beyond the Grey Mountains somewhere to the south.\n");
    add_item(({"grass", "green grass", "lawn"}),
        "Lush and deep, this grass covers the tall hill in a dark " +
        "green blanket.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    reset_room();
}
