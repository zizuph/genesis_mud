/*
 *  /d/Emerald/telberin/dock/hidden_beach.c
 *
 *  A deserted beach just south of the main gates of Telberin.
 *  This is a modified version of the beach Shiva coded
 *  long ago to be the entrance into the domain. I've gotten
 *  rid of the carriage to the wedding chapel. I guess we'll
 *  have to figure out a new place for that (maybe.)
 *
 *  Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 *
 *  Added fishing     : August 2021 (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit "/d/Emerald/std/room";

#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <subloc.h>
#include <ss_types.h>
#include <stdproperties.h>

#define WATER_SUBL "_water_subloc"


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    object obelisk;

    set_short("a deserted rocky beach beneath the walls of Telberin");
    set_em_long("A rocky beach extends out from the base of a vast"
      + " section of the walls which ring the city of Telberin. This"
      + " beach is rather secluded, and is hidden from the road which"
      + " leads into the city just over a slope to the north. A path"
      + " makes its way between tall grasses which grow along the slope,"
      + " hiding this beach from the view of most travellers. A strange"
      + " heap of stones has been deposited close to the shore. @@subl_desc@@");
    add_item( ({ "stone", "stones", "heap", "heap of stones" }),
        "This curious pile of stones has been deposited close to the"
      + " shoreline. Each stone itself is black and glossy, smoothened"
      + " by waves from the lake. Upon closer inspection, you conclude"
      + " that this is not an ordinary pile of rocks, but an entrance"
      + " to a cenote of some sort.\n");
    add_item( ({ "beach", "rocky beach", "shore", "shoreline" }),
        "This beach is spread out beneath the towering frame of a"
      + " section of the outer wall of Telberin which looms to the"
      + " northeast. Rocks and pebbles form the surface of the area,"
      + " growing larger as they near the stone base of the wall,"
      + " where many large boulders are piled.\n");
    add_item( ({ "rock", "rocks", "pebble", "pebbles", "ground",
                 "down", "floor" }),
        "Rocks and pebbles are everywhere underfoot, spreading out"
      + " to form the surface of this beach.\n");
    add_item( ({ "base", "base of the wall", "stone base",
                 "boulder", "boulders", "pile", "pile of boulders",
                 "large boulder", "large boulders" }),
        "Large boulders are piled along the base of the mighty"
      + " wall which towers over this beach to the northwest. They"
      + " have been slowly piled along the beach over centuries of"
      + " storm.\n");
    add_item( ({ "streaks", "mud", "streaks of mud", "streak of mud",
                  "mud streak", "mud streaks" }),
        "Mud has collected along the lower portions of the city"
      + " wall, perhaps due to times which the water level has been"
      + " higher than it is now.\n");
    add_item( ({ "line", "lines", "water line", "water lines" }),
        "The water lines along the base of the wall would indicate"
      + " that this beach has been, at times, submerged completely"
      + " beneath the waters of the lake.\n");
    add_item( ({ "wall", "walls", "vast section", "section of walls",
                 "walls of telberin", "city walls", "massive walls",
                 "massive wall", "great wall", "great walls",
                 "city wall" }),
        "The walls of Telberin are vast and mighty. Here, they tower"
      + " above the beach, rising at least one hundred feet into"
      + " the air. Streaks of mud have darkened much of the lower"
      + " portions of stone, and it is clear that at times the water"
      + " of the lake has risen higher, creating water lines along"
      + " the wall.\n");
    add_item( ({ "telberin", "city", "city of telberin", "city" }),
        "All that is visible of the city from here is the outward"
      + " face of this massive wall which protects its southwestern"
      + " flank.\n");
    add_item( ({ "sky", "up" }),
        "The sky is clear and breezy here beside the lake waters.\n");
    add_item( ({ "water", "lake", "waters", "lake water",
                 "waters of the lake", "lake telberin", "telberin lake",
                 "waters of lake telberin" }),
        "Lake Telberin surrounds the Island upon which the city has"
      + " been built. Here, it laps quietly at the rocky shore before"
      + " spreading out a great distance to the south and west.\n");
    add_item( ({ "island", "mainland" }),
        "The island that houses the city of Telberin is rocky and"
      + " tall. Most of the mainland has been incorporated into the"
      + " confines of the city itself.\n");
    add_item( ({ "slope", "grassy slope", "north", "slope to the north",
                 "hill", "hillside" }),
        "A grassy slope runs up from this beach toward the road which"
      + " leads into the city. Tall grasses along the hill form a"
      + " visual barrier, preventing you from seeing any of the"
      + " travellers beyond its top.\n");
    add_item( ({ "grass", "grasses", "tall grass", "tall grasses" }),
        "The grasses along the hill sway in the occasional breeze."
      + " They are extremely tall in places, specifically along"
      + " the top of the slope, where they prevent this beach"
      + " from being readily seen by the casual passerby.\n");
    add_item( ({ "path", "winding path", "dirt path" }),
        "A dirt path winds up the slope, passing between the tall"
      + " grasses as it leads toward the road above to the north.\n");
    add_item( ({ "road" }),
        "The road is not visible from this beach.\n");


    add_prop("_live_i_can_fish", "freshwater");
    add_prop(ROOM_I_LIGHT, 4);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_subloc(WATER_SUBL, this_object());

    obelisk = clone_object(TELBERIN_DIR + "dock/mist_isle_obelisk");
    obelisk->set_no_show_composite(1);
    obelisk->move(this_object(), WATER_SUBL);

    add_exit("telberin_gates", "north");
    add_exit("/d/Emerald/south_shore/room/cenote", "enter", 0, 1, 1);

    set_no_exit_msg( ({ "northeast", "east" }),
        "You halt before the towering wall of the city.\n");
    set_no_exit_msg( ({ "southeast", "south", "southwest", "west",
                        "northwest" }),
        "You pause at the waters edge, but don't feel like getting"
      + " yourself all wet.\n");
} /* create_emerald_room */


public string
subl_desc()
{
    if (!this_player()->query_subloc())
    {
        return "The waters of Lake Telberin ripple quietly against"
             + " the shore.\n";
    }

    return "From your position here in the lake, you notice a dark, " +
        "pointed stone jutting up from the surface of the water.\n";
}


public mixed
subloc_access(string subloc, object ob, string access, object for_obj)
{
    if (access == SUBLOC_ACCESS_MANIP)
    {
        return "It is too far away.\n";
    }

    return 1;
}

public string
show_subloc(string subloc, object ob, object for_obj)
{
    object *livings = FILTER_LIVE(subinventory(subloc));
    int i;
    string *names;

    if (sizeof(livings))
    {
        if ((i = member_array(for_obj, livings)) >= 0)
        {
            names = ({ "You" });
            livings = exclude_array(livings, i, i);
        }
        else
        {
            names = ({});
        }

        livings = FILTER_CAN_SEE(livings, for_obj);
        names += map(livings, &->query_the_name(for_obj));
        return capitalize(COMPOSITE_WORDS(names)) +
            (((sizeof(names) == 1) && (names[0] != "You")) ? 
            " is " : " are ") + "wading in the lake.\n";
    }

    return "";
}

public int
into_water()
{
    string msg;

    if (this_player()->query_subloc() == WATER_SUBL)
    {
        write("You are already wading in the water.\n");
        return 1;
    }

    this_player()->move(this_object(), WATER_SUBL);
    write("You wade out into the cold water.\n");
    msg = " wades out into the lake.\n";
    say(({ METNAME + msg, TART_NONMETNAME + msg, "" }));
    return 1;
}

public int
out_of_water()
{
    string msg;

    if (this_player()->query_subloc() != WATER_SUBL)
    {
        write("You aren't in the water, though.\n");
        return 1;
    }

    this_player()->move(this_object());
    write("You wade back to the shore.\n");
    msg = " wades onto the shore.\n";
    say(({ METNAME + msg, TART_NONMETNAME + msg, "" }));
    return 1;
}

public varargs int
wade(string str)
{
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (parse_command(str, ({}), "[out] [into] / [to] / [in] [the] " +
        "'water' / 'lake'"))
    {
        return into_water();
    }

    if (parse_command(str, ({}), "[out] [of] [from] [the] 'water' / 'lake'") ||
        parse_command(str, ({}),
            "[back] [to] / [onto] [the] 'shore' / 'land'"))
    {
        return out_of_water();
    }

    notify_fail(capitalize(query_verb()) + " where?\n");
    return 0;
}

public int
enter(string str)
{
    if (strlen(str) &&
        parse_command(str, ({}), "[the] 'water' / 'lake'"))
    {
        return into_water();
    }

    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;
}

public int
leave(string str)
{
    if (strlen(str) &&
        parse_command(str, ({}), "[the] 'water' / 'lake'"))
    {
        return out_of_water();
    }

    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;
}

public int
swim(string str)
{
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        "[in] [to] [into] [the] 'water' / 'waters' / 'lake'"
      + " [of] [the] [lake] [telberin]"))
    {
        return 0; /* can't parse player syntax */
    }

    write("The water here is quite shallow. You probably couldn't"
      + " do much more than wade in the water unless you were"
      + " farther from shore.\n");
    return 1;
}

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


public void
init()
{
    ::init();

    add_action(wade, "wade");
    add_action(wade, "walk");
    add_action(wade, "go");
    add_action(enter, "enter");
    add_action(leave, "leave");
    add_action(leave, "exit");
    add_action(swim, "swim");
    add_action(swim, "dive");
    add_action(do_drink, "drink");
}
