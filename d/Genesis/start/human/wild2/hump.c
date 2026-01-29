/* 
 *	hump.c			Styles.   3 Mar 1993
 *
 *  Modified by Varian - October 5, 2015
 *
 *  Added fishing properties allowing fishing from bridge - Arman 2021
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/start/human/wild2/base";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

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
    set_items_driver();

    set_short("Humpbacked bridge");
    set_long("You are standing in the middle of a stone bridge, old " +
        "and weathered, which jumps across the rushing waters of the " +
        "Diamond River as it cuts through the fields " +
        "of tall green grass. The bridge follows along a dusty " +
        "road which falls out of the jagged, snow-capped heights of the " +
        "Grey Mountains to west and tumbles its way east to the port of " +
        "Sparkle as it stands proudly on the shining waters of the Pen " +
        "Sea. Immediately to the west, you can see what appears to be " +
        "a busy crossroads, while to the east you can just make out the " +
        "tall stockade which surrounds Sparkle.\n");

    add_exit(THIS_DIR + "crossroad","west");
    add_exit(TOWN_DIR + "vill_gate","east");

    set_no_exit_msg(({"southwest","south","southeast","northwest","north",
            "northeast"}),
        "This bridge looks like it is pretty high above the river here! " +
        "Just trying to walk over the edge would probably be suicidal.\n");

    add_item(({"here"}),
        "You are standing in the middle of a stone bridge, old " +
        "and weathered, which jumps across the rushing waters of the " +
        "Diamond River as it cuts through the fields " +
        "of tall green grass. The bridge follows along a dusty " +
        "road which falls out of the jagged, snow-capped heights of the " +
        "Grey Mountains to west and tumbles its way east to the port of " +
        "Sparkle as it stands proudly on the shining waters of the Pen " +
        "Sea. Immediately to the west, you can see what appears to be " +
        "a busy crossroads, while to the east you can just make out the " +
        "tall stockade which surrounds Sparkle.\n");
    add_item(({"bridge", "humbacked bridge", "old bridge", "stone bridge"}),
        "This bridge is quite old, if not ancient! Yet, the stones " +
        "and mortar are still in rather good repair. The humped back " +
        "of the bridge arches high with across the " +
        "rushing waters of the Diamond River which run from the north " +
        "to the south. On either side of the bridge, two thick stone " +
        "rails have been constructed to prevent travellers from " +
        "falling into the river by accident.\n");
    add_item(({"initials", "carving", "carvings"}),
        "On one of the stones there is a carving reading: " +
        "K + P = TRUE! and on another stone, someone else has carved: " +
        "J + C = Forever. While on the rail, yet another carving " +
        "reads: A loves C.\n");
    add_item(({"stone", "stones"}),
        "The entire bridge is made of stone set firmly into mortar. On " +
        "some of the stones, you can see some carvings.\n");
    add_item(({"river", "stream", "diamond river"}),
        "The rushing waters of the Diamond River rush down from the " +
        "mountains which cover the horizon to the northwest, cross " +
        "under the bridge here running south, before turning east " +
        "and emptying out into the blue waters of the Pen Sea which " +
        "spreads out to the east. The water itself looks cool and " +
        "fresh, a quick drink would probably taste great right now!\n");
    add_item(({"water", "waters", "river", "stream", "diamond river"}),
        "You can hear the waters of the Diamond River as they rush along " +
        "beneath the old stone bridge as well as the shining blue water " +
        "of the Pen Sea as it sparkles in the distance across the " +
        "eastern horizon.\n");
    add_item(({"field", "fields", "hill", "hills"}),
        "Wild fields of tall green grass roll over gentle hills all " +
        "around you. The fields are unbroken save for the Diamond " +
        "River and the dusty road which crosses it here at the bridge.\n");
    add_item(({"grass", "green grass", "tall grass"}),
        "The grass is tall and green, growing abundantly enough to " +
        "cover the fields all around you.\n");
    add_item(({"road", "dusty road", "dust"}),
        "The road on either side of the bridge is just dirt, " +
        "hard-packed from years of use, yet blowing up clouds of dust " +
        "with every gust of wind that rushes past. The road leads " +
        "east towards the tall stockade which surrounds the town " +
        "of Sparkle, and west towards a busy crossroads.\n");
    add_item(({"crossroads", "crossroad"}),
        "The road west of here seems to intersect with a wide and " +
        "busy road which runs north and south in the shadow of the " +
        "mountains which dominate the western horizon.\n");
    add_item(({"mortar", "cement"}),
        "The grey mortar which cements the stones of the bridge into " +
        "place appears to be in very good repair, especially for a " +
        "bridge this old! It is obvious that someone has taken " +
        "especially good care of it.\n");
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
        "To the east, you can see the road leading into the town of " +
        "Sparkle, the legendary port city which is the hub of the " +
        "Pen Sea. The town appears to be quite lively, as if it " +
        "never sleeps, a feeling which is only accented by the fact " +
        "that there appears to be an endless stream of ships which " +
        "are either arriving or departing from the great port.\n");
    add_item(({"rail", "rails"}),
        "Two thick stone rails cover the north and south sides of the " +
        "bridge, preventing unwary travellers from falling into the " +
        "river by accident. You happen to notice that someone has " +
        "carved something into the southern rail.\n");
    add_item(({"southern rail", "south rail"}),
        "This is a thick, stone rail which is a part of the bridge " +
        "which spans the Diamond River here. It appears that someone " +
        "has carved 'A loves C' on the surface here.\n");
    add_item(({"northern rail", "north rail"}),
        "This is a thick, stone rail which is a part of the bridge " +
        "which spans the Diamond River here.\n");

    set_drink_from(({"stream", "river", "diamond river"}));

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(LIVE_I_CAN_FISH, "freshwater");

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        init
 * Description  :        Sets up commands for the player
 */
void
init()
{
    ::init();
    init_drink();
    add_action("do_climb","climb");
}
/* init */

/*
 * Function name:        drink_message
 * Description  :        Provides a description for drinking from the river
 */
public void
drink_message(string from)
{
    write("You walk over to the eastern bank of the river, " +
        "bend down and cup your hands to drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}
/* drink_message */

/*
 * Function name:        do_climb
 * Description  :        Allows players to climb under the bridge
 * Returns      :        int 0 - Prompts for syntax
 *                       int 1 - Climbs the bridge
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
        "[down] [under] [over] [the] [humpbacked]"
      + " [hump-backed] [[north] [northern] [below]"
      + " [hump] [backed] [back] [humpback] [hump-back]"
      + " [stone] 'bridge' / 'rail'") &&
        str != "down")
    {
        notify_fail("Where do you wish to climb?\n");
        return 0;
    }

    write("You climb over the northern rail and go down"
      + " under the bridge.\n");
    SAYBB(" climbs over the side of the bridge");
    TP->move_living("M", "/d/Sparkle/area/bandit/ban1",1,0);
    SAYBB(" arrives climbing down the bridge.");

    return 1;
} /* do_climb */