/*
 *  /d/Sparkle/area/tutorial/farm/crossroad_4.c
 *
 *  This road is west of the crossroads north of Greenhollow. It leads
 *  to the mountain trail and up to Krolock's Castle.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 *  Updated July 22, 2016 by Gronkas - fixed a typo
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <cmdparse.h>  /* for NORMAL_ACCESS */
#include <macros.h>    /* for QCTNAME       */
#include <ss_types.h>  /* for SS_CLIMB      */

/* definitions */
#define  NEEDED_SKILL        10  /* the necessary climbing skill */

/* prototypes */
public void        create_silverdell();
public int         check_exit();
public void        init();
public string      describe(string arg);
public int         do_climb(string arg);
public int         do_tie(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("on a road beneath steep cliffs");
    set_long("The road travels west up into the mountain cliffs here."
      + " A ways to the east, it appears to meet with a crossroads."
      + " A mudslide seems to have occurred to the west, causing the"
      + " road to be interrupted by a steep dropoff.\n\n");

    add_outdoor_items();
    add_road_items();
    add_forest_items();
    add_river_items();
    add_mountain_items();

    add_item( ({ "cliff", "cliffs", "mountain cliff",
                 "mountain cliffs" }),
        "The cliffs to the west loom forbodingly down over you. They"
      + " appear more treacherous the farther west you look.\n");
    add_item( ({ "crossroads", "crossroad", "east" }),
        "East of here, the crossroads are visible.\n");
    add_item( ({ "here", "area" }), long);
    add_item( ({ "mudslide", "mud", "road", "slide", "west",
                 "blockage", "path", "drop", "dropoff",
                 "drop off", "sheer dropoff" }),
        "Just to the west, a mudslide has washed away the gradual"
      + " downward slope of the path, turning it instead into a"
      + " sheer dropoff that will probably require some ingenuity"
      + " to maneuver. You notice a tree stump beside the path here"
      + " at the top of the dropoff.\n");
    add_item( ({ "stump", "tree", "tree stump", "stump of a tree" }),
        &describe("stump"));
    add_item( ({ "rope" }), &describe("rope"));

    add_exit(CLIFFS_DIR + "cliffroad_1", "west", check_exit, 1, 0);
    add_exit("crossroads", "east");

    reset_room();
} /* create_silverdell */


/*
 * Function name:        check_exit
 * Description  :        see if the player is allowed to travel this
 *                       direction
 * Returns      :        1 - don't allow, 0 - allow
 */
public int
check_exit()
{
    if (!CHECK_TUTORIAL_BIT(MUDSLIDE_BIT))
    {
        write("A mudslide has washed out the road which travels west,"
          + " resulting in a sheer dropoff. You notice a stump beside"
          + " the edge of the dropoff, maybe you can figure something"
          + " out here.\n");

        return 1;
    }

    write("The dropoff to the west makes travel impossible in that"
      + " direction. You could try to <climb> down the rope that is tied"
      + " to the stump, though.\n");

    return 1;
} /* check_exit */


/*
 * Function name:        describe
 * Description  :        provide a state-dependant description of things
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - the description
 */
public string
describe(string arg)
{
    switch(arg)
    {
        case "stump":
            if (!CHECK_TUTORIAL_BIT(MUDSLIDE_BIT))
            {
                return "Gazing at the stump that is right beside the"
                  + " dropoff, and measuring the distance to the ground"
                  + " below, you figure that if you had even a fairly"
                  + " short rope, you could probably <tie> it to the"
                  + " stump and manage to travel west.\n";
            }

            return "The stump has your rope tied to it. It would"
              + " probably be possible to <climb> down the rope.\n";
            break;
        case "rope":
            if (!CHECK_TUTORIAL_BIT(MUDSLIDE_BIT))
            {
                return 0;
            }

            return "The rope you tied to the stump is just where you"
              + " left it. You could probably try to <climb> down it.\n";
            break;
    }

    return 0; /* should never happen. */
} /* describe */



/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_climb, "climb");
    add_action(do_tie, "tie");
    add_action(do_tie, "untie");
} /* init */


/*
 * Function name:        do_climb
 * Description  :        allow the player to try to climb down the rope
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}), "[down] [the] 'rope'"))
    {
        if (arg != "down")
        {
            return 0; /* bad or unexpected syntax */
        }
    }

    if (!CHECK_TUTORIAL_BIT(MUDSLIDE_BIT))
    {
        write("You don't dare to try climbing down the sheer dropoff."
          + " Perhaps if there was a rope tied to something it would be"
          + " feasible.\n");
        return 1;
    }

    if (this_player()->query_skill(SS_CLIMB) < NEEDED_SKILL)
    {
        write("Peering down over the edge, you feel very insecure"
          + " about the idea of climbing down the rope. You'd better"
          + " train your climbing skill a bit more first.\n");
        return 1;
    }

    write("You climb down the rope, and find yourself again on the"
      + " road which travels west.\n");

    //this_player()->move_living("M", CLIFFS_DIR + "cliffroad_1", 1, 0);
    moveto("M", CLIFFS_DIR + "cliffroad_1" , 1, 0);
    tell_room(this_object(), QCTNAME(this_player())
      + " climbs down the rope and disappears.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " climbs down the rope and arrives from the east.\n",
        this_player());

    this_player()->add_fatigue(-10);

    return 1;
} /* do_climb */


/*
 * Function name:        do_tie
 * Description  :        allow players to try to tie a rope to the
 *                       stump
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - success, 0 - otherwise
 */
public int
do_tie(string arg)
{
    mixed  *obj;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %i 'to' [the] 'stump'", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        if (query_verb() == "untie" &&
            parse_command(arg, ({}),
            "[the] 'rope' [from] [the] [stump]"))
        {
            notify_fail("The rope is tied too tight. You cannot untie"
              + " it.\n");
            return 0;
        }

        notify_fail("Tie what to what?\n");
        return 0;
    }

    if (!obj[0]->id("_tutorial_rope"))
    {
        notify_fail("You can't tie that to anything. Perhaps if you"
          + " tried a rope?\n");
        return 0;
    }

    if (CHECK_TUTORIAL_BIT(MUDSLIDE_BIT))
    {
        write("You've already tied a rope to the stump. It is still"
          + " there for you to use.\n");
        return 1;
    }

    if (obj[0]->query_length() > 10)
    {
        write("You work with the rope a bit, separating a ten foot"
          + " length from its coil. You then tie the separated length"
          + " to the stump, and let it dangle over the edge to the"
          + " ground below.\n");

        obj[0]->decrease_length();
        SET_TUTORIAL_BIT(MUDSLIDE_BIT);

        return 1;
    }

    write("You tie the rope to the stump and let it dangle over the"
      + " edge to the ground below.\n");

    obj[0]->remove_object();
    SET_TUTORIAL_BIT(MUDSLIDE_BIT);

    return 1;
} /* do_tie */

