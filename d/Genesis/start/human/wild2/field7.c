/* 	
 * field7.c			Styles.   3 Mar 1993
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
    set_items_sparkle();
    set_items_field();
    set_items_darkroad();
    set_herbs();

    set_short("Dark Road");
    set_long("You are walking along the Dark Road as it cuts through " +
        "grassy wide fields that stretch out far to the west. The highway " +
        "connects the city of Sparkle to Dwarfheim and the lands of the " +
        "north. As you gaze out east of the road, you notice " +
        "a heavy mist has settled across the wet moorlands that " +
        "stretch out east towards the Pen Sea, barely visible in the " +
        "distance. Rising up ahead of you to the north, the jagged " +
        "peaks of the Grey Mountains climb higher as they march " +
        "further west until they dominate the northern and western " +
        "horizons. In the distance to the south, you can see the " +
        "winding shape of a river cutting through the fields. A small " +
        "path leads west off the highway, running towards a mound in the " +
        "distance.\n");

    add_trees(0);

    add_exit(THIS_DIR + "field11","north");
    add_exit(THIS_DIR + "ruin","west");
    add_exit(THIS_DIR + "bridge_n","south");
    add_exit(THIS_DIR + "field10", "northwest",0,1,1);
    add_exit(THIS_DIR + "field6", "southwest",0,1,1);

    set_no_exit_msg(({"northeast","southeast","east"}),
        "Dense mists swirl across the wet moors that begin east of the " +
        "Dark Road. There does not appear to be a safe way to enter the " +
        "moors in this direction.\n");

    add_item(({"moor", "moors", "moorland"}),
        "The gentle green foothills of the Grey Mountains turn into " +
        "a misty moorland as they flatten out to the east. There are " +
        "two bridges you can see that can take you across the river " +
        "to the heart of the moorlands.\n");
    add_item(({"river","diamond river"}),
        "This appears to be the Diamond River, cutting through the fields " +
        "as it winds its way south towards Sparkle before emptying out into " +
        "the Pen Sea.\n");
    add_item(({"mist","mists"}),
        "Dense mists swirl and settle across the vast moorlands that "  +
        "stretch out to the east.\n");
    add_item(({"path","dirt path","small path","small dirt path"}),
        "This small dirt path seems to be leading towards a mound of " +
        "some sort in the distance.\n");
    add_item(({"mound","ruin","ruins","building"}),
        "It is hard to say, but it seems like this mound is the ruins " +
        "of some ancient building. Although, who would build something " +
        "out in the middle of these plains is a mystery to you.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}