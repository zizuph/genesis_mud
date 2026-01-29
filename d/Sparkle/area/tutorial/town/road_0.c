/*
 *  /d/Sparkle/area/tutorial/town/road_0.c
 *
 *  This room teaches about the options commands.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    11  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public int         hint(string arg);
public void        reset_room();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("a dirt road winding down a hill");
    set_long("You are travelling along the slopes of a hill covered"
      + " with deep green grasses. A dirt road zigzags its way from"
      + " the base of the hill to the north up to the summit south of"
      + " here. Off in the distance, you see a town to the north.\n\n");

    add_road_items();
    add_outdoor_items();
    add_mountain_items();
    add_forest_items();
    add_river_items();

    add_item( ({ "grass", "green grass", "grasses", "green grasses",
                 "deep green grass", "deep green grasses" }),
        "Grass grows all along the hillside and spreads out beside the"
      + " path.\n");
    add_item( ({ "hill", "base", "base of a hill", "hill base",
                 "base of the hill", "summit" }),
        "The base of the hill is down the path north of here. The summit"
      + " rises above to the south. The hill itself is quite beautiful,"
      + " rising into the sky with its green grasses blowing in the"
      + " breeze.\n");
    add_item( ({ "town", "greenhollow", "roof", "rooftop", "roofs",
                 "rooftops", "first rooftops", "building", "buildings",
                 "town of greenhollow" }),
        "To the north, a number of buildings are visible rising over the"
      + " grass. This path leads toward the town of Greenhollow.\n");

    prevent_attacks();
    reset_room();

    add_exit("hilltop", "south");
    add_exit("road_1", "north");
} /* create_silverdell */

/*
 * Function name:        init
 * Description  :        add some commands to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("Here, you might want to set your preferences using the"
      + " <options> command. Read the tutorial sign for more information"
      + " on how to do so.\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object   npc;

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


