/*
 *  /d/Sparkle/area/tutorial/woods/river.c
 *
 *  This is the eastern shore of the Silverdell River directly west
 *  of the Sterling Woods.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 *
 *  Fixed to remove all cloves when swimming river
 *  Lavellan 20100609   (maybe not the best method...)
 *
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <macros.h>    /* for QCTNAME */
#include <ss_types.h>  /* for SS_SWIM */

/* definitions */
#define  NEEDED_SKILL        10  /* the necessary swimming skill */

/* prototypes */
public void        create_silverdell();
public int         check_exit();
public void        init();
public int         do_swim(string arg);
public int         do_drink(string str);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("beneath the Sterling Woods on the shores of the"
      + " Silverdell");
    set_long("You stand on the eastern shore of the Silverdell River"
      + " beneath the tall trees of the Sterling wood which looms over"
      + " you to the east. It looks as if the road once continued into"
      + " the woods, but it has long since fallen into disuse, and"
      + " become so overgrown as to be completely obscured within"
      + " a few short paces. West, a bridge travels across the"
      + " waters of the river.\n\n");

    add_outdoor_items();
    add_road_items();
    add_forest_items();
    add_river_items();
    add_mountain_items();

    add_item( ({ "shore", "east shore", "eastern shore" }),
        "The shore of the river is muddy, but placid.\n");
    add_item( ({ "far shore" }),
        "The far shore of the river is visible in the distance.\n");
    add_item( ({ "river", "silverdell river", "water", "waters",
                 "river water", "river waters", "water of the river",
                 "waters of the river", "bridge" }),
        "The Silverdell River flows swiftly past, winding its way"
      + " south to disappear in the distance. A bridge has been built"
      + " to span its course, leading west.\n");
    add_item( ({ "wood", "woods", "forest", "tree", "trees", "east",
                 "sterling woods", "path", "road" }),
        "Just east of here, the path leads into the Sterling Woods,"
      + " where it is quickly lost among the undergrowth. The trees"
      + " grow closely together, making it difficult to see far beyond"
      + " the outskirts of the forest.\n");

    add_exit("forest_1c", "east");
    add_exit(FARM_DIR + "crossroad_3", "west", check_exit, 1, 0);

    //This room isn't instanced.
    instance_entrance = 1;

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
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        write("The bridge has been completely destroyed. You see no"
          + " way to cross over the ravine.\n");
        return 1;
    }

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return 0;
    }

    write("Unfortunately, the bridge has been badly burned, and is no"
      + " longer fit for travel. You might be able to try to <swim>"
      + " across the river.\n");
    return 1;
} /* check_exit */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_swim, "swim");
    add_action(do_swim, "dive");
    add_action(do_swim, "wade");
    add_action(do_swim, "cross");
    add_action(do_drink, "drink");
} /* init */


/*
 * Function name:        do_swim
 * Description  :        allow the player to try to swim across the river
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_swim(string arg)
{
    object  herb;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[in] [to] [into] [across] [the] [wide] 'river' / 'water'"
      + " / 'ravine' / 'west' / 'w'"))
    {
        return 0; /* bad or unexpected syntax */
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        write("There is nothing to " + query_verb() + " into except"
          + " the thorns - the water has ceased to flow!\n");
        return 1;
    }

    if (this_player()->query_skill(SS_SWIM) < NEEDED_SKILL)
    {
        write("You just don't feel confident enough. You'll need to"
          + " train your swim skill a bit higher first.\n");
        return 1;
    }

    write("You dive into the water, and swim through the swift waters"
      + " to the far shore.\n");

    if (objectp(herb = present("_tutorial_clove", this_player())))
    {
        write("Ack!!\n"
            + "You seem to have lost your cloves in the strong"
            + " current. Perhaps if you had a backpack to put items"
            + " in, you wouldn't lose things so easily.\n");
        //herb->remove_object();
        foreach(object x: all_inventory(this_player()))
        {
            if (x->id("_tutorial_clove"))
                x->remove_object();
        };
    }

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        write("Stepping out of the water, you notice that you probably"
          + " could have just taken the bridge.\n");
    }

    this_player()->move_living("M", FARM_DIR + "crossroad_3", 1, 0);
    tell_room(this_object(), QCTNAME(this_player())
      + " dives into the river and swims west.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " swims up to the shore from the east and steps, dripping, out"
      + " of the river.\n", this_player());

    this_player()->add_fatigue(-10);

    return 1;
} /* do_swim */


/*
 * Function name:        do_drink
 * Description  :        let players drink from the river
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
do_drink(string str)
{
    int     i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (!parse_command(str, ({ }),
        "[the] [water] [from] [the] 'river'"))
    {
        notify_fail("What do you wish to drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("You kneel down and scoop some river water to your mouth."
          + " You seem to have drunk your fill.\n");
    }
    else
    {
        write("You kneel down and scoop some river water to your mouth."
          + " You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " drinks some water from the"
        + " river.\n");

    return 1;
} /* do_drink */
