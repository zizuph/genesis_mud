/*
 *  /d/Sparkle/guilds/new_merc/rooms/path2.c
 *
 *  The entrance to the Merc Guild area. On a bridge crossing the
 *  River just northeast of Camp.
 *
 *  Created April 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <filter_funs.h> /* for FILTER_LIVE */
#include <macros.h>      /* for QCTNAME     */


/* Global Variables */
public string     *QR_Team = ({ "bauxite",
                                "gorbjr",
                                "golgatan",
                                "redshift",
                             });
/* Prototypes */
public void        create_merc_room();
public int         do_dive(string arg);
public void        init();
public int         climb_bridge(string arg);

public int         align_shift(string arg);

/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("on a sturdy wooden bridge spanning the "
      + RIVERNAME + " River");
    set_long("The " + RIVERNAME + " River flows pleasantly beneath"
      + " the sturdy wooden bridge on which you stand. Just to the"
      + " southwest the bridge opens onto the grounds of the Mercenary"
      + " Guild, which has taken up operations in an old logging"
      + " camp. Northeast, the path runs toward the main road.\n\n");

    try_item( ({ "river", lower_case(RIVERNAME),
                 lower_case(RIVERNAME) + " river",
                 "river " + lower_case(RIVERNAME), "water" }),
        "It flows gently but somewhat noisily beneath the bridge"
      + " you stand on.\n");
    try_item( ({ "main road", "northeast" }),
        "The main road is visible in the distance to the northeast.\n");
    try_item( ({ "southwest" }),
        "To the southwest, the path leaves the bridge and enters"
      + " the grounds of the Mercenary Guild.\n");
    try_item( ({ "bridge", "wooden bridge", "sturdy bridge",
                 "sturdy wooden bridge" }),
        "The bridge is extremely sturdy, having been constructed to"
      + " support the traffic of an active logging camp. You feel"
      + " quite confident looking down into the river from its"
      + " frame.\n");
    try_item( ({ "frame", "frame of the bridge" }),
        "Sturdy. Built to last!\n");
    try_item( ({ "camp", "mercenary camp", "logging camp",
                 "mercenary guild", "old logging camp", "guild" }),
        "The camp spreads out before you to the southwest. You'll be"
      + " able to see more detail if you travel closer.\n");
    try_item( ({ "road", "path" }),
        "The path crosses a bridge here, travelling into the camp to"
      + " the southwest and up to the main road to the northeast.\n");

    add_cmd_item( ({ "river", "water", RIVERNAME + " river" }),
                  ({ "drink" }),
        "The bridge is a bit too high above the surface of the"
      + " water to reach it.\n");

    add_delay_cmd_item( ({ "bridge", "wooden bridge", "sturdy bridge",
                           "sturdy wooden bridge" }),
                        "search",
                        "searching the bridge",
                        10,
                        "You begin searching the bridge, looking for"
                      + " anything that looks interesting.\n",
                        "Hmmm ... you notice a shallow bank underneath"
                      + " the bridge beside the water of the river. You"
                      + " might be able to climb down to it.\n");

    add_river_view();
    add_bridge_view();
    add_outdoor_view();
    add_lodge_view();
    add_mill_view();

    add_exit("path1", "northeast");
    add_exit("path3", "southwest");

    set_no_exit_msg( ({ "north", "northwest", "west", "south",
                        "southeast", "east" }),
        "You wander to the edge of the bridge and peer into the"
      + " river doubtfully. Seeing no point in getting wet, you don't"
      + " proceed.\n");

    setuid();
    seteuid(getuid());
} /* create_merc_room */


/*
 * Function name:        do_dive
 * Description  :        Allow players to try to swim in the river or
 *                       dive off the bridge.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_dive(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (query_verb() == "drink")
    {
        if (parse_command(arg, ({}),
            "[from] [the] 'river' / 'water'"))
        {
            notify_fail("The bridge is a bit too high above the surface"
              + " of the water to reach it.\n");
            return 0;
        }

        return 0;
    }
        
    if (!parse_command(arg, ({}),
        "[off] [of] [in] [into] [the] 'bridge' / 'water' / 'river' / "))
    {
        notify_fail("Perhaps you want to " + query_verb() + " in the"
          + " river?\n");
        return 0;
    }

    notify_fail("The river isn't very deep, and looks positively"
      + " dreadful for swimming. Better to stay dry in this case.\n");
    return 0;
} /* do_dive */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_dive, "dive");
    add_action(do_dive, "swim");
    add_action(do_dive, "enter");
    add_action(do_dive, "jump");
    add_action(do_dive, "drink");
    add_action(climb_bridge, "climb");
    add_action(align_shift, "testeralign");
} /* init */


/*
 * Function name:        align_shift
 * Description  :        Allow testers from the Quest Reform team to
 *                       shift their alignment here.
 * Arguments    :        string arg - what was typed 
 * Returns      :        1 - success, 0 - failure
 */
public int
align_shift(string arg)
{
    int     align;

    if (!IN_ARRAY(this_player()->query_real_name(), QR_Team))
    {
        return 0;
    }

    if (!strlen(arg) ||
        !parse_command(arg, ({}),
         "'good' / 'evil' / 'neutral'"))
    {
        notify_fail("Useage: <testeralign good/evil/neutral>\n");
        return 0;
    }

    switch(arg)
    {
        case "good":
            align = 1200;
            break;
        case "evil":
            align = -1200;
            break;
        default:
            align = 0;
            break;
    }

    write("You have shifted your alignment to pure " + arg + ".\n");
    this_player()->set_alignment(align);
    return 1;
} /* align_shift */



/*
 * Function name:        climb_bridge
 * Description  :        allow players to climb under the bridge
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_bridge(string arg)
{
    mixed  *targets;
    mixed  *non_seers;
    object  destination;

    if (!strlen(arg))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [under] [underneath] [beneath] [to] [the] [sturdy]"
      + " [wooden] [shallow] 'bridge' / 'bank'"))
    {
        if (arg == "down")
        {
            notify_fail("Climb down? Can you be more specific?\n");
        }
        else
        {
            notify_fail("You don't seem to be able to climb there.\n");
        }
        return 0;
    }

    targets = FILTER_LIVE(all_inventory(this_object()));
    non_seers = filter(targets, not @ this_player()->check_seen);

    destination = safely_load_master_file(ROOM_DIR + "under_bridge");

    write("You climb underneath the bridge.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " climbs down over"
      + " the side of the bridge and disappears beneath.\n",
        non_seers + ({ this_player() }));

    targets = FILTER_LIVE(all_inventory(destination));
    non_seers = filter(targets, not @ this_player()->check_seen);

    tell_room(destination, QCTNAME(this_player()) + " climbs down from"
      + " the top of the bridge and lands on the bank here.\n",
        non_seers + ({ this_player() }));

    TELL_G(capitalize(this_player()->query_real_name()) + " climbs under the"
      + " Mercenary bridge!");

    this_player()->move_living("M", destination, 1, 0);
    return 1;
} /* climb_bridge */
