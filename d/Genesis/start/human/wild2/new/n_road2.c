/*     
 * n_road2.c                       Styles.   3 Mar 1993
 *
 *  Modified by Varian - Oct 2015
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/start/human/wild2/base";

#include "/d/Sparkle/area/bandit/wild.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

public void drink_message(string from);
public int do_climb(string str);

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_sparkle();
    set_items_darkroad();
    set_items_driver();
    set_herbs();

    set_short("Dark road");
    set_long("You are walking along the hard-packed dirt of the Dark Road " +
            "which leads north from Sparkle towards the ancient homeland " +
            "of the Dwarves. To the west of the road, grassy foothills " +
            "rise up quickly in a mountain spur to transform into the " +
            "jagged heights of the Grey Mountains which cover the entire " +
            "western horizon. To the east, a wooden bridge jumps across the " +
            "rushing waters of the Diamond River and follows a small path " +
            "that appears to be swallowed by the moors which stretch out " +
            "into the distance. Even further to the east, barely visible on " +
            "the horizon, is the legendary Pen Sea, filled with all manner " +
            "of ships sailing to far and distant lands.\n");

    add_trees(0);

    add_exit("/d/Genesis/start/human/wild2/new/n_road2a","north");
    add_exit("/d/Genesis/start/human/wild2/new/n_road1","south");
    add_exit("/d/Sparkle/guilds/mercs/room/start", "east");
    add_exit("/d/Genesis/start/human/wild2/new/n_road2", "northeast",
        "@@riv@@", 1,1);
    add_exit("/d/Genesis/start/human/wild2/new/n_road2", "southeast",
        "@@banks@@", 1,1);
    add_exit("/d/Genesis/start/human/wild2/new/n_road2", "west",
        "@@spur@@", 1,1);
    add_exit("/d/Genesis/start/human/wild2/new/n_road2", "northwest",
        "@@spur@@", 1,1);
    add_exit("/d/Genesis/start/human/wild2/new/n_road2", "southwest",
        "@@spur@@",1,1);

    add_item(({"bridge", "wooden bridge"}),
             "This old wooden bridge reaches out from the Dark Road as it " +
             "stretches over the rushing waters of the Diamond River " +
             "and connects to a path which wanders through the eastern " +
             "moors.\n");
    add_item(({"moor", "moors", "moorland"}),
             "The gentle green foothills of the Grey Mountains turn into " +
             "soggy moorland as they flatten out to the east. There is a " +
             "small path on the other side of the bridge which appears " +
             "to flow into the heart of the moors.\n");
    add_item(({"path", "small path"}),
             "There is a small dirt path on the other side of the Diamond " +
             "River, which appears to lead deeper into the moorlands. You " +
             "can reach it by crossing the wooden bridge which is beside " +
             "you.\n");
    add_item(({"field", "fields", "hill", "hills"}),
             "Wild fields of tall green grass roll over gentle hills all " +
             "around you before falling into the moors which lie east of " +
             "the Diamond River.\n");
    add_item(({"grass", "green grass", "tall grass"}),
             "The grass is tall and green, growing abundantly enough to " +
             "cover the fields all around you.\n");
    add_item(({"road", "dark road", "dirt"}),
             "This wide swath of hard-packed dirt is better known as the " +
             "Dark Road. The road leads north away from Sparkle, across " +
             "the dwarven lands before it supposedly reaches the legendary " +
             "city of Larton. \n");
    add_item(({"larton", "larstown"}),
             "Larton is whispered only as rumour and legends by most people " +
             "these days, it was once in close contact with Sparkle but " +
             "now appears to be all but forgotten.\n");
    add_item(({"crossroads", "crossroad"}),
             "Far in the distance to the south, there appears to be a " +
             "crossroads where a wide road flows out of the Grey Mountains " +
             "and intersects with the Dark Road before crossing the " +
             "Diamond River and entering the town of Sparkle.\n");
    add_item(({"mountain", "mountains"}),
             "Stretching across the western horizon you can see an endless " +
             "line of jagged, snow-capped mountain peaks as they pierce the " +
             "sky. These are the Grey Mountains, a legendary fixture in the " +
             "countryside surrounding Sparkle. It is said that the " +
             "traditional homeland of the dwarves, Dwarfheim is hidden " +
             "somewhere to the north, while somewhere in the south, goblins " +
             "have tunneled deep into the heart of the mountains, " +
             "establishing a realm of their own.\n");
    add_item(({"sea", "pen sea"}),
             "Spreading out to the east, farther than the eye can see, is " +
             "the Pen Sea. Nearby, to the east, you can see the famous " +
             "port of Sparkle, a major hub of activity with a constant " +
             "stream of ships arriving and departing from even the most " +
             "remote corners of the world.\n");
    add_item(({"stockade", "wall", "walls"}),
             "Looking east from the bridge, your eye follows the dusty " +
             "road as it cuts its way through the green fields and ends " +
             "at the tall stockade which surrounds the town of Sparkle. " +
             "Composed of tall wooden posts, with the tops sharpened into " +
             "points, this massive wall helps to protect the town, keeping " +
             "it safe from any potential invaders.\n");
    add_item(({"sparkle", "town", "city", "village", "port"}),
             "Somewhere over the moors, off to the southeast, lies Sparkle," +
             "the legendary port city which is the hub of the " +
             "Pen Sea. The town appears to be quite lively, as if it " +
             "never sleeps, a feeling which is only accented by the fact " +
             "that there appears to be an endless stream of ships which " +
             "are either arriving or departing from the great port.\n");
    add_item(({"bank","riverbank","ravine","steep banks","banks",
            "steep bank","steep ravine"}),
        "A steep ravine dives down towards the Diamond River just east " +
        "of the Dark Road here.\n");
    add_item(({"spur","mountain spur"}),
        "A rugged spur of mountains cuts through the valley just west " +
        "of the road, making passage in that direction impossible.\n");

    set_drink_from(({"stream", "river", "diamond river"}));

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

void
init()
{
    ::init();
    init_drink();
    add_action("do_climb","climb");
}

/*
 * Function name:        drink_message
 * Description  :        Gives a description of drinking from the river
 */
public void
drink_message(string from)
{
    write("You bend down, cup your hands and drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}
/* drink_message *?

/*
 * Function name:        do_climb
 * Description  :        Allows players to climb down the bridge
 * Returns      :        int 1 - Mortal climbs down
 *                       int 0 - Prompts for syntax
 */
public int
do_climb(string str)
{
    if(!strlen(str))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        "[down] [under] [over] [the] [wood]"
      + " [old] 'bridge'") &&
        str != "down")
    {
        notify_fail("Where do you wish to climb?\n");
        return 0;
    }

    write("You down the side of the old bridge.\n");
    SAYBB(" climbs down the side of the old bridge.");
    TP->move_living("M",THIS_DIR + "riv4",1,0);
    SAYBB(" arrives climbing down the side of the old bridge.");

    return 1;
} 
/* do_climb */

/*
 * Function name:        banks
 * Description  :        Gives an explanation for why the mortal cannot travel
                         in this direction
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
 * Function name:        riv
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the river in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
riv()
{
    write("The wide blue waters of the Diamond River prevents you from " +
        "going in that direction. If you want to cross the river, why " +
        "don't you use the bridge to the east?\n");
    return 1;
}
/* riv */

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