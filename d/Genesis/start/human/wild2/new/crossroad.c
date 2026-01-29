/* 	
 * crossroad.c			Styles.   3 Mar 1993
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
    set_herbs();

    set_short("At the crossroad");
    set_long("You are standing in the middle of a well-travelled crossroads " +
        "just west of the city of Sparkle, nestled in the middle of a " +
        "wide valley full of fields and rivers, with three major highways " +
        "that seem to run in all directions. Just east of the crossroads, " +
        "an ancient bridge made from fieldstones arches over the rushing " +
        "waters of the Diamond River before the road continues to the " +
        "gates of Sparkle. The three highways are the Bright Road, " +
        "which goes south towards the Jade Forest. The Dark Road, which " +
        "runs north towards Dwarfheim and the Orc Road, which appears to " +
        "be the most heavily travelled, which heads west right into the " +
        "heart of the Grey Mountains.\n");
    
    add_trees(1);

    add_exit(THIS_DIR + "n_road1","north");
    add_exit(THIS_DIR + "orc_road1","west");
    add_exit(THIS_DIR + "s_road1a","south");
    add_exit(THIS_DIR + "crossroad", "northwest", "@@spur@@", 1,1);
    add_exit(THIS_DIR + "crossroad", "northeast", "@@banks@@", 1,1);
    add_exit(THIS_DIR + "crossroad", "southwest", "@@rough@@", 1,1);
    add_exit(THIS_DIR + "crossroad", "southeast", "@@banks@@", 1,1);
    
    // Only reason for this that I can think of is to stop wandering monsters
    // from entering Sparkle. But the ogre mage is the only one anywhere near,
    // and it would be unlikely that he makes it here. It blocked horses too!
    ////////add_exit(THIS_DIR + "hump","east","@@eblock", 0);
    add_exit(THIS_DIR + "hump","east");
    
    add_item(({"here"}),
        "You are standing in the middle of a well-travelled crossroads " +
        "just west of the city of Sparkle, nestled in the middle of a " +
        "wide valley full of fields and rivers, with three major highways " +
        "that seem to run in all directions. Just east of the crossroads, " +
        "an ancient bridge made from fieldstones arches over the rushing " +
        "waters of the Diamond River before the road continues to the " +
        "gates of Sparkle. Pristine white stones form the Bright Road " +
        "that runs south from here towards the Jade forest and the " +
        "wilderness beyond. While a heavily travelled highway known as " +
        "the Orc Road rumbles west, slowly climbing the foothills of the " +
        "jagged Grey Mountains before cutting through the high pass to " +
        "the traditional homeland of the orcs that lays on the other " +
        "side. Another path, the Dark Road, heads north from the " +
        "crossroads, winding its way north in the direction of Dwarfheim " +
        "and other lands north of the mountains.\n");
    add_item(({"spur","mountain spur"}),
        "A rugged spur of mountains cuts through the valley just northwest " +
        "of the road, making passage in that direction impossible.\n");
    add_item(({"road","roads","crossroad","crossroads","path","paths",
            "highway","highways"}),
        "You are standing at the busy crossroads west of Sparkle. The Orc " +
        "Road begins its long climb up towards the High Pass to the west, " +
        "while the Dark Road begins its long journey past Dwarfheim " +
        "towards Larton to the north. The white stones of the Bright " +
        "Road trail off towards the Jade Forest in the south and finally " +
        "the road east crosses a stone humpbacked bridge on its way " +
        "through the tall stone walls of the city of Sparkle.");
    add_item(({"dark road"}),
        "This is a raised highway running across the fields north of " +
        "Sparkle as it climbs up towards the treacherous pass through the " +
        "Grey Mountains known as the Renegade Cut. Few travellers seem " +
        "to follow this road these days, as the pass is now controlled " +
        "by bandits, but it is said that the northern terminus of the " +
        "road is the city of Larton.\n");
    add_item(({"orc road"}),
        "Thousands of flat stones have been cut and raised above the " +
        "land to build the Orc Road. The road leads directly west out of " +
        "Sparkle, climbing the high pass, before settling down into the " +
        "Orc Forest and eventually to the elven lands of Faerie.\n");
    add_item(({"bright road"}),
        "This road looks well maintained. The highway itself is made " +
        "of large white stones, split and cut into hexagonal shapes and " +
        "interlocked upon a raised surface. The paving stones are rounded, " +
        "sloping towards the white edgestones that frame the entire length " +
        "of the road. The entire Bright Road travels from Sparkle in the " +
        "north and through the Jade Forest before it reaches the wilderness " +
        "to the south.\n");
    add_item(({"bridge", "humbacked bridge", "old bridge", "stone bridge"}),
        "Just east of the crossroads is an ancient humpbacked stone bridge " +
        "which arches high above the rushing waters of the Diamond River " +
        "that rush past on their way to the Pen Sea.\n");
    add_item(({"wall", "walls", "wood wall", "wooden walls",
            "sparkle wall", "sparkle walls","stockade","wooden stockade"}),
        "A tall wooden wall graces the eastern horizon, surrounding the " +
        "legendary city of Sparkle.\n");
    add_item(({"sparkle gate","city gate","gate","gates"}),
        "The road east of the crossroads seems to flow straight into " +
        "the gates of Sparkle. You are too far away to see any details " +
        "of the gates, only that they stand open granting access beneath " +
        "the tall wooden walls that surround the city.\n");
    add_item(({"sparkle","city","town","village","port"}),
        "The city of Sparkle, widely hailed as the greatest port in the " +
        "world, lies just east of these crossroads. High wooden walls " +
        "are visible on the horizon, as the road east leads towards the " +
        "city gates.\n");
    add_item(({"diamond river","water","waters","river"}),
        "The Diamond River rushes past just east of these crossroads, " +
        "tunneling its way under an ancient stone bridge.\n");
    add_item(({"bridge","stone bridge","ancient bridge","humpbacked bridge",
            "ancient stone bridge","fieldstone","fieldstone bridge",
            "fieldstones"}),
        "Built from hundreds of fieldstones, this ancient stone bridge " +
        "is humpbacked in shape, arching over the rushing blue waters " +
        "of the Diamond River.\n");
    add_item(({"east horizon","eastern horizon","east"}),
        "Immediately east of you here, the horizon is dominated by the " +
        "wooden stockade surrounding the city of Sparkle, and the blue " +
        "waters of the Pen Sea that spreads across the horizon beyond.\n");
    add_item(({"ground","down"}),
        "You are standing at a crossroads of four roads, each running " +
        "in one of the cardinal directions. The rest of the land " +
        "around you here seems to be covered in grassy fields with a " +
        "wide river cutting through them just east of here.\n");
    add_item(({"bank","riverbank","ravine","steep banks","banks",
            "steep bank","steep ravine"}),
        "A steep ravine dives down towards the Diamond River just east " +
        "of the Dark Road and Bright Road here.\n");
    add_item(({"spur","mountain spur"}),
        "A rugged spur of mountains cuts through the valley just west " +
        "of the road, making passage in that direction impossible.\n");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
    /*
    clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
    */
}

/*
 * Function name:        eblock
 * Description  :        I don't know what this does!
 */
int
eblock()
{
    if (this_player()->query_merc_dog())
        return 0;

    if (query_ip_number(this_player()))
        return 0;
    return 1;
}
/* eblock */

/*
 * Function name:        banks
 * Description  :        Gives an explanation for why the mortal cannot travel
                         down the ravine
 * Returns      :        int 1 - denies moving along the exit path
 */
int
banks()
{
    write("The ravine that dives steeply down towards the river looks too " +
        "dangerous for you to climb down!\n\n " +
        "You are unable to go in that direction!\n");
    return 1;
}
/* banks */

/*
 * Function name:        spur
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the mountains in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
spur()
{
    write("In order to go in that direction, you would need to have the " +
        "skills of an expert mountain climber. It looks like you will have " +
        "to go in another direction for now.\n");
    return 1;
}
/* spur */

/*
 * Function name:        rough
 * Description  :        Gives an explanation for why the mortal cannot travel
                         in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
rough()
{
    write("The land looks a little rugged in that direction, you will have " +
        "to follow either the Orc Road west or the Bright Road south " +
        "instead.\n");
    return 1;
}
/* rough */

/*
 * Function name:        wizinfo
 * Description  :        Just a string of information for wizards!
 */
string
wizinfo()
{
    return ("If you are to make any caravan or other mass transportation\n"+
            "that will arrive to Sparkle, this is as far as it should go.\n"+
            "You may have it drive by here and pick up passengers etc. but\n"+
            "do not take it into town. The only exception are ships. They\n"+
            "will of course arrive and depart in the harbour. \n");
}
/* wizinfo */