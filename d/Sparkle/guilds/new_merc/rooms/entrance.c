/*
 *  /d/Sparkle/guilds/new_merc/rooms/entrance.c
 *
 *  Just within the doors of the Lodge which houses the Mercenary Guild.
 *  Players might want to wipe their feet here!
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();
public int         wipe_feet(string arg);
public void        init();
public int         leave_lodge();
public int         climb_stairs(string arg);
public int         stair_msg(string which);


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("within the entrance hall of the Mercenary lodge");
    set_long("You stand within the entrance to the Mercenary"
      + " guild lodge. All around are the pleasant natural tones of"
      + " the lumber which makes up the walls of this large structure."
      + " Naturally lit from the many windows, an aura of peace and"
      + " security welcomes you and your fellow Mercenaries home from"
      + " your travels. Large staircases travel up to the second floor"
      + " both north and south of the entrance, and an entry hall"
      + " is visible to the west. Large doors open eastward onto the"
      + " grounds of the camp outside. A large mat has been placed"
      + " on the floor here.\n\n");

    try_item( ({ "mat", "large mat" }),
        "A large mat is here for people who feel like wiping their"
      + " feet as they come in.\n");
    try_item( ({ "door", "doors", "large door", "large doors",
                 "lodge door", "lodge doors", "doors of the lodge",
                 "door of the lodge", "east" }),
        "The doors of the lodge are directly to the east here. You see"
      + " a few guards standing on this side of the threshhold, peering"
      + " out into the grounds.\n");
    try_item( ({ "entrance", "here", "area", "hall",
                 "entrance to the mercenary guild", "guild entrance",
                 "entrance to the lodge", "lodge entrance", "entryway",
                 "entry", "grand entry", "grand entryway", "room" }),
        "This entryway is fairly grand in scale. Your eyes wander up to"
      + " the ceiling high above, framed by rafters. With the natural"
      + " light coming in from the windows, this place is quite"
      + " picturesque.\n");
    try_item( ({ "tone", "tones", "natural tone", "natural tones",
                 "pleasant tone", "pleasant tones",
                 "pleasant natural tone", "pleasant natural tones",
                 "pleasant natural tones of the lumber",
                 "natural tones of the lumber" }),
        "Rustic ... rugged ... beautiful in a way ...\n");
    try_item( ({ "aura", "aura of peace", "peaceful aura",
                 "aura of peace and security", "aura of security",
                 "secure aura" }),
        "You feel perfectly at home here. Its always nice to be back"
      + " in the lodge after a long journey.\n");
    try_item( ({ "stair", "stairs", "step", "steps", "staircase",
                 "staircases", "large staircase", "large staircases" }),
        "Two large staircases travel up to the second floor of the"
      + " lodge, one to the north and one to the south of the entrance.\n");
    try_item( ({ "north", "south" }),
        "A large staircase travels up to the second floor in that"
      + " direction.\n");
    try_item( ({ "second floor", "second floor of the lodge" }),
        "The second floor of the lodge isn't visible from here, but you"
      + " could reach it climbing the stairs to the north or south.\n");
    try_item( ({ "entry hall", "west" }),
        "The entrance opens onto a larger entry hall just to the"
      + " west.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("path3", "east", leave_lodge, 1, 0);
    add_exit("n_landing", "north", &stair_msg("north"), 2, 0);
    add_exit("s_landing", "south", &stair_msg("south"), 2, 0);
    add_exit("entry_hall", "west");

    set_no_exit_msg( ({ "northwest", "northeast", "southeast",
                        "southwest" }),
        "You poke around the corners of the entrance hall, but find no"
      + " way to proceed that direction.\n");

    setuid();
    seteuid(getuid());
} /* create_merc_room */


/*
 * Function name:        wipe_feet
 * Description  :        allow players to wipe their feet on the mat
 *                       so they don't track dirt all over the
 *                       guildhall
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
wipe_feet(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[off] [my] 'feet' / 'boots' / 'boot' / 'foot' / 'shoe' / 'shoes'"
      + " [off] [on] [the] [mat]"))
    {
        notify_fail("Perhaps you'd like to wipe your feet on the mat?\n");
        return 0;
    }

    write("You take a minute to wipe your dirty feet on the mat.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
        + " wipes " + this_player()->query_possessive() + " dirty feet"
        + " off on the mat.\n", this_player());

    this_player()->add_prop(MERC_WIPED_FEET, 1);
    return 1;
} /* wipe_feet */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(wipe_feet, "wipe");
    add_action(wipe_feet, "clean");
    add_action(climb_stairs, "climb");
} /* init */


/*
 * Function name:        leave_lodge
 * Description  :        When a player leaves the lodge, we remove
 *                       their MERC_WIPED_FEET prop - their boots are
 *                       again dirty!
 * Returns      :        int 0 - always
 */
public int
leave_lodge()
{
    if (this_player()->query_prop(MERC_WIPED_FEET))
    {
        this_player()->remove_prop(MERC_WIPED_FEET);
    }

    return 0;
} /* leave_lodge */


/*
 * Function name:        climb_stairs
 * Description  :        let the players try to climb the stairs with
 *                       a command rather than just directional movement
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_stairs(string arg)
{
    string   *stair_dir = ({ "north", "south", "n", "s" });

    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [the] [large] 'stair' / 'stairs' / 'stairway' / 'stairways'"))
    {
        notify_fail("Climb which stairway, the north or the south?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [large] %p 'stair' / 'stairs' / 'stairway' /"
      + " 'stairways'", stair_dir))
    {
        notify_fail("Climb either the north or south stairways, perhaps?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        notify_fail("At this point, we would try to move the player"
          + " up the stairs using command(). Since you are a wizard,"
          + " that won't work. Just type the direction command yourself,"
          + " please.\n");
        return 0;
    }

    this_player()->command("$" + stair_dir[0]);
    return 1;
} /* climb_stairs */


/*
 * Function name:        stair_msg
 * Description  :        print a message to player and room when the
 *                       stairs are climbed
 * Arguments    :        string which - which direction did they go,
 *                                      "north" or "south" ?
 * Returns      :        int 0 - always
 */
public int
stair_msg(string which)
{
    mixed  *targets = FILTER_LIVE(all_inventory(this_object()));
    mixed  *non_seers = filter(targets, not @ this_player()->check_seen);

    write("You climb the stairs up to the second floor.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " climbs up the"
      + " stairs to the second floor.\n", non_seers + ({ this_player() }));

    /* Any people in the broom closet should hear someone going up the
     * south stairway, too.
     */
    if (which == "south")
    {
        tell_room(ROOM_DIR + "broom_closet",
            "The ceiling creaks, and you can hear footsteps proceeding"
          + " up the staircase that is right above your head.\n");
    }

    return 0;
} /* stair_msg */