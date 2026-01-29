/*
 *  /d/Emerald/north_shore/dock.c
 *
 *  From here, players may take a ferry from the north
 *  shore of Lake Telberin to the City itself. This dock
 *  is kept under guard, as it is a key point to the
 *  defense of the shore.
 *
 *  Copyright (c) March 2002, by Cooper Sherry (Gorboth)
 *
 *  Revision history: Aug 2021 - Added fishing (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* prototypes */
public void        create_del_rimmon();
public int         do_drink(string arg);
public int         do_stuff(string arg);
public void        init();
public int         notify_gorboth();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("near a dock along the north shore of"
      + " Lake Telberin");
    set_em_long("A large dock has been built here, extending"
      + " south into the waters of Lake Telberin. The shores"
      + " of the lake run east and west, forming a gap between the"
      + " water and a long stretch of forest which rests beneath"
      + " the feet of the Blackwall Mountains to the north. A"
      + " path leads from the docks to the east, where a large"
      + " structure is visible.\n");

    add_item( ({ "dock", "pier" }),
        "Built of many planks and large beams of wood, this"
      + " pier looks as if it could service many large ships"
      + " at a time, yet only a few small rowing vessels"
      + " are lining its span.\n");
    add_item( ({ "plank", "beam", "beams", "beam of wood",
                 "planks", "large beam", "large beams",
                 "beam of wood", "wooden beam", "wooden beams",
                 "beams of wood", "large beams of wood" }),
        "The dock is impressively constructed. There are beams"
      + " so massive, they look to be almost as large as a"
      + " full grown fir tree. Clearly, this pier was created"
      + " to serve a purpose larger than its current lot.\n");
    add_item( ({ "vessel", "vessels", "rowing vessel",
                 "small vessel", "small vessels",
                 "small rowing vessel", "small rowing vessels",
                 "rowing vessels", "many small rowing vessels",
                 "boat", "row boat", "boats", "row boats",
                 "small boat", "small boats", "small row boats",
                 "small row boat" }),
        "Small row boats are moored along the pier, where they"
      + " bob lazily in the water. They are completely dwarfed"
      + " by the enormity of the docks.\n");
    add_item( ({ "lake", "lake telberin", "telberin lake",
                 "water", "south", "waters" }),
        "Lake Telberin expands to the south, extending nearly"
      + " as far as the eye can see. Its waters are a crystal"
      + " blue, glinting with light where they air catches"
      + " the surface. Quite a long way off, the City of"
      + " Telberin is visible only as a tiny speck which rides"
      + " the waves at the far southern end of the lake.\n");
    add_item( ({ "telberin", "city", "city of telberin",
                 "speck", "tiny speck" }),
        "The City of Telberin is only barely visible from here."
      + " It rises from the waters of the lake in the far south,"
      + " where it appears as only a tiny speck.\n");
    add_item( ({ "shore", "shores", "shore of the lake",
                 "shores of the lake", "lake shore", "north shore",
                 "north shores", "northern shore", 
                 "northern shores", "lakeshore" }),
        "The shores of the lake here are built up with many"
      + " large rocks, against which the waves occasionally send"
      + " crashes of spray. Above the rocks, a stretch of smaller"
      + " stones runs north to meet with the first trees of the"
      + " forest. The shores continue east and west, rimming"
      + " the lake.\n");
    add_item( ({ "large rocks", "wave", "waves", "spray",
                 "crashes", "crashes of spray" }),
        "Waves occasionally crash up against the large rocks"
      + " which have built up the level of the lake shore here.\n");
    add_item( ({ "forest", "woods", "tree", "trees",
                 "stretch of forest", "long stretch of forest" }),
        "To the north, a thin stretch of woods separates the"
      + " shores of the lake from the feet of the Blackwall"
      + " Mountains.\n");
    add_item( ({ "mountain", "mountains", "blackwall mountains",
                 "feet of the blackwall mountains", "cliff",
                 "cliffs", "tall cliff", "tall cliffs" }),
        "Tall cliffs rise beyond the forest to the north, the"
      + " first feet of the Blackwall Mountains which fill the"
      + " horizon in that direction.\n");
    add_item( ({ "sky", "up" }),
        "The sky above is bright and brilliant.\n");
    add_item( ({ "ground", "down", "floor" }),
        "The ground is rocky and uneven here, especially as one"
      + " approaches the edge of the lake. A path travels from"
      + " the docks to the east.\n");
    add_item( ({ "path", "trail", "well-worn path",
                 "well worn path", "worn path", "worn trail",
                 "stone", "stones", "small stone", "smaller stone",
                 "small stones", "smaller stones",
                 "stretch of smaller stones", "stretch",
                 "well-worn trail", "well worn trail" }),
        "A well-worn path leads from the docks travelling in"
      + " the direction of the structure to the east. You notice"
      + " what appear to be a few old tracks curving away from"
      + " the main path.\n");
    add_item( ({ "track", "tracks", "old track", "old tracks",
                 "few old tracks", "a few old tracks" }),
        "A few old tracks curve to the north, heading away from"
      + " the main path. They are very overgrown, and only"
      + " visible due to their deep ruts, which appear to have"
      + " been made by wagon wheels. They disappear north,"
      + " leading into the forest.\n");
    add_item( ({ "rut", "ruts", "deep rut", "deep ruts" }),
        "Deep ruts distinguish very old tracks which run toward the"
      + " forest to the north. The ground has been carved by the"
      + " passage of strong wheels running the same track over many"
      + " years. However, they have now filled in with grass and"
      + " other vegetation, suggesting that they have not been used"
      + " any time recently.\n");
    add_item( ({ "east", "structure", "structure to the east",
                 "eastern structure", "outpost", "fortress",
                 "large outpost", "large fortress" }),
        "East of here, a large outpost of some kind stands between the"
      + " lakeshore and the forest.\n");
    add_item( ({ "ladder", "ladders", "wooden ladder",
                 "wooden ladders", "wood ladder", "wood ladders" }),
        "Wooden ladders run from the sides of the pier down to beneath"
      + " the water. Next to each ladder, a rowboat has been moored.\n");

    add_cmd_item( ({ "track", "tracks", "old track", "old tracks",
                     "few old tracks", "a few old tracks" }),
                  ({ "search" }),
        "You inspect the tracks more closely, and find that they are"
      + " quite deep in places, where it appears as if wagon wheels"
      + " dug out the earth in what must have been a fairly regular"
      + " passage. The tracks are now overgrown, and do not appear"
      + " to have been used at all for a very long time. They lead"
      + " into the woods to the north.\n");

    add_exit(DELRIMMON_DIR + "trail/forest_path", "north",
        notify_gorboth, 1, 1);
    add_exit("/d/Emerald/north_shore/outpost/gate01", "east");

    add_prop(OBJ_I_CONTAIN_WATER, -1);

    set_no_exit_msg( ({ "northeast", "northwest" }),
        "You wander a bit along the edge of the forest, and then"
      + " return to the shore.\n");
    set_no_exit_msg( ({ "west", "southwest", "southeast" }),
        "You walk along the shore for a bit in that direction, and"
      + " then return to the dock.\n");
    set_no_exit_msg( ({ "south" }),
        "You halt at the edge of the water, and peer at the lake."
      + " To attempt to swim across the lake would seem futile,"
      + " though an accomplished swimmer might be up to it.\n");

    add_prop("_live_i_can_fish", "freshwater");

} /* create_del_rimmon */


/*
 * Function name:        do_stuff
 * Description  :        let players interact with certain objects
 *                       in the room
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - otherwise
 */
public int
do_stuff(string arg)
{
    string  swim_room;

    if (query_verb() == "swim" || query_verb() == "dive")
    {
        if (!strlen(arg))
        {
            notify_fail(capitalize(query_verb()) + " where?\n");
            return 0;
        }

        if (!parse_command(arg, ({}),
            "[in] [to] [into] [across] [the] 'water' / 'lake' [telberin]"))
        {
            return 0; /* can't parse the syntax */
        }

        if (this_player()->query_skill(SS_SWIM) < 50)
        {
            notify_fail("Peering into the often turbulent waters of"
              + " Lake Telberin, you feel sure you lack the necessary"
              + " skill to traverse the waters on your own.\n");
            return 0;
        }

        if (this_player()->query_fatigue() < 30)
        {
            notify_fail("You are too tired to try that right now.\n");
            return 0;
        }

        this_player()->add_fatigue(-50);
        this_player()->reveal_me();

        swim_room = "/d/Emerald/telberin/dock/ferry_dock";

        this_player()->catch_tell("You dive off the dock and swim"
          + " with powerful strokes across the water. Reaching the"
          + " northernmost pier of Telberin, you climb out of the"
          + " water to stand dripping before the city.\n");
        tell_room(swim_room, QCTNAME(this_player()) + " suddenly"
          + " appears in the distance to the north, swimming across"
          + " the lake with powerful strokes. Presently, "
          + this_player()->query_pronoun() + " reaches the pier and"
          + " clambers up over the side to stand dripping beside"
          + " you.\n");
        this_player()->move_living("M", swim_room, 1, 0);
        tell_room(this_object(), QCTNAME(this_player()) + " dives off"
          + " the dock and swims with powerful strokes toward the"
          + " city. " + capitalize(this_player()->query_pronoun())
          + " soon disappears into the distance and is lost from"
          + " sight.\n");
        return 1;
    }

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[in] [to] [into] [the] [row] [rowing] 'boat' / 'boats' /"
      + " 'rowboat' / 'rowboats'"))
    {
        return 0; /* player used odd syntax */
    }

    write("You climb down one of the ladders on the pier, and climb"
        + " into one of the rowboats which line the dock. You notice"
        + " as you sit how enormous these piers look compared to the"
        + " size of these crafts. At one time there must have been"
        + " a need to have larger vessels serviced at this dock."
        + " You climb back up to the pier, and make your way back to"
        + " the shore.\n");

    return 1;
} /* do_stuff */


/*
 * Function name:        do_drink
 * Description  :        let players drink from the spring
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
        "[from] [the] 'water' / 'lake' [from] [the] [lake]"
      + " [telberin]"))
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
        write("You scoop a handful of lake water, and sip it"
            + " cautiously. It is icy cold, and very refreshing."
            + " You seem to have drunk your fill.\n");
    }
    else
    {
        write("You scoop a handful of lake water, and sip it"
            + " cautiously. It is icy cold, and very refreshing."
            + " You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " stoops and drinks some water"
        + " from the lake.\n");

    return 1;
} /* do_drink */



/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_stuff, "climb");
    add_action(do_stuff, "enter");
    add_action(do_stuff, "get");
    add_action(do_stuff, "use");
    add_action(do_stuff, "sit");
    add_action(do_drink, "drink");
    add_action(do_stuff, "dive");
    add_action(do_stuff, "swim");

    if (interactive(this_player()))
    {
        catch(call_other(
            "/d/Emerald/north_shore/outpost/clone_handler", "??"));
    }
} /* init */


/*
 * Function name:        notify_gorboth
 * Description  :        tell gorboth stuff
 */
public int
notify_gorboth()
{
    string  pl = capitalize(this_player()->query_real_name());

    find_living("gorboth")->catch_msg("\n"
      + "    ****  " + pl + " approaches the Del Rimmon! ****\n\n");
}
