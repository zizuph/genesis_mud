/*
 *  /d/Sparkle/area/tutorial/town/street_7.c
 *
 *  This road leads out of Greenhollow to the unprotected
 *  areas beyond. It teaches about death.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    32  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public int         check_exit();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("at the border of Greenhollow before the North Gate");
    set_long("You stand before the north gate of Greenhollow. This"
      + " is the border of the town, beyond which the protection"
      + " of Lars does not extend. Though exciting and rewarding,"
      + " the adventures beyond this point are also dangerous."
      + " Travelling north will take you through the gate out of"
      + " town. A dirt road winds south through a grove of trees.\n\n");

    add_road_items();
    add_outdoor_items();

    add_item( ({ "town", "greenhollow", "city", "building",
                 "buildings" }),
        "The buildings of the town are not visible here. You can enter the"
      + " main part of the city by travelling to the south through a"
      + " grove of trees.\n");
    add_item( ({ "tree", "trees", "grove", "grove of trees", "south" }),
        "South, the road passes into town, heading through a grove of"
      + " trees that is visible in the distance.\n");
    add_item( ({ "gate", "north", "north gate",
                 "north gate of greenhollow" }),
        "A tall gate rises to the north, signifying the border between"
      + " the town of Greenhollow and the lands beyond. Passing through"
      + " will take you into dangerous lands of adventure and"
      + " opportunity.\n");

    prevent_attacks();
    reset_room();

    add_exit(FARM_DIR + "crossroad_1", "north", check_exit, 1, 0);
    add_exit("street_6", "south");
} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
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
    write("Sure, here's a hint. Once you walk through the gate to"
      + " the north, you will be in unfamiliar territory. You should"
      + " start making your own map if you have not already done"
      + " so, adding new rooms as you explore.\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name:        check_exit
 * Description  :        print a message to the player when they
 *                       pass through the exit.
 * Returns      :        0 - we allow them through
 */
public int
check_exit()
{
    write("\nYou feel suddenly less safe, as if Lars can no longer"
      + " protect you here.\n\n");
    return 0;
} /* check_exit */

