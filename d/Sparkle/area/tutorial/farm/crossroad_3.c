/*
 *  /d/Sparkle/area/tutorial/farm/crossroad_3.c
 *
 *  This road is east of the crossroads north of Greenhollow. It leads
 *  to a bridge that crosses the Silverdell River.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
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
public string      describe(string arg);
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
    set_short("on a road beside the Silverdell River");
    set_long(&describe("long"));

    add_outdoor_items();
    add_road_items();
    add_forest_items();
    add_river_items();
    add_mountain_items();

    add_item( ({ "far shore" }),
        "The far shore of the river is visible in the distance, resting"
      + " beneath the Sterling Woods.\n");
    add_item( ({ "crossroads", "crossroad", "west" }),
        "West of here, the crossroads are visible.\n");
    add_item( ({ "here", "area" }), &describe("long"));
    add_item( ({ "bridge", "burned bridge", "ruined bridge", "supports",
                 "support", "ruined supports", "strong supports" }),
                 &describe("bridge"));
    add_item( ({ "river", "silverdell river", "river silverdell",
                 "water", "waters", "flowing water", "ravine",
                 "thorn", "thorns", "wide ravine", "crevasse",
                 "deadly crevasse", "east" }), &describe("river"));
    add_item( ({ "northeast", "dell", "earth", "scorched earth",
                 "shallow dell" }),
        &describe("dell"));
    add_item( ({ "structure", "large structure", "guild", "guildhall",
                 "patrol guild", "patrol guildhall" }),
        "A guildhall is southeast of here, a fair distance off.\n");

    add_exit("dell", "northeast");
    add_exit(WOODS_DIR + "river", "east", check_exit, 1, 0);
    add_exit("crossroads", "west");
    add_exit(TUTORIAL_DIR + "guild/joinroom", "southeast");

    reset_room();
} /* create_silverdell */


/*
 * Function name:        describe
 * Description  :        provide a status dependant descriptions
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - various descriptions of things
 */
public string
describe(string arg)
{
    string  cross_txt = "The road travels east from the crossroads to ";

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        switch(arg)
        {
            case "long":
                return cross_txt + "run up against a dark ravine"
                  + " that was formerly filled with the flowing waters"
                  + " of the Silverdell river. A destroyed bridge to"
                  + " the east hangs useless over thorns which have grown"
                  + " to fill the devastated former waterway. Northeast,"
                  + " the road descends through scorched earth into"
                  + " a shallow dell. A seemingly unharmed structure is"
                  + " to the southeast.\n\n";
                break;
            case "bridge":
                return "The bridge has been entirely destroyed. Its"
                  + " ruined supports cling miserably to both shores"
                  + " of the river.\n";
                break;
            case "river":
                return "A wide ravine to the east marks the former"
                  + " pathway of the Silverdell River. Its waters have"
                  + " vanished now, leaving a deadly crevasse which is"
                  + " now filled with cruel and impassable thorns.\n";
                break;
            case "dell":
                return "Though the earth has been scorched, the dell"
                  + " still appears to be traversable.\n";
                break;
        }
    }

    switch(arg)
    {
        case "long":
            if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                return cross_txt + "run up against the beautiful flowing"
                  + " waters of the Silverdell River. The bridge has"
                  + " been rebuilt, it seems, and now spans the river"
                  + " travelling from one shore to the next. Northeast,"
                  + " the road bends to travel down into a peaceful"
                  + " green dell. A large structure is to the southeast.\n\n";
            }

            return cross_txt + "run up against the swift waters of the"
              + " Silverdell River. A bridge which looks to once have"
              + " served as passage over the river has been"
              + " partially burned, and looks unfit for travel. Northeast,"
              + " the road bends to descend into a shallow dell. A large"
              + " structure is to the southeast.\n\n";
            break;
        case "bridge":
            if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                return "Apparently, the influence of Baron von Krolock has"
                  + " been entirely banished from the land. The bridge has"
                  + " been rebuilt greater than its prior incarnation. Its"
                  + " strong supports confidently span the waters of the"
                  + " River, allowing any who might wish to do so passage"
                  + " to the far bank.\n";
            }
            return "The bridge to the east looks to have once been"
              + " very strong and sturdy, easily capable of supporting"
              + " the weight of a carriage and horse. Unfortunately,"
              + " it appears as if someone has set fire to the mid"
              + "section of the bridge, rendering it useless for"
              + " crossing the River.\n";
            break;
        case "river":
            return "Directly to the east, the swift waters of the"
              + " Silverdell River flow beside the road. A bridge"
              + " has been erected to travel to the far shore which"
              + " is visible in the distance just beneath the Sterling"
              + " Woods.\n";
            break;
        case "dell":
            return "The road travels northeast down into a shallow dell"
              + " that runs alongside the river.\n";
            break;
    }
} /* describe */


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
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[in] [to] [into] [across] [the] [wide] 'river' / 'water'"
      + " / 'ravine' / 'east' / 'e'"))
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
      + " to the far shore.\n\n");

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        write("Stepping out of the water, you notice that you probably"
          + " could have just taken the bridge.\n");
    }

    this_player()->move_living("M", WOODS_DIR + "river", 1, 0);
    tell_room(this_object(), QCTNAME(this_player())
      + " dives into the river and swims east.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " swims up to the shore from the west and steps, dripping, out"
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
