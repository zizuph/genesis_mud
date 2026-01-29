/*
 *  /d/Sparkle/guilds/new_merc/rooms/under_bridge.c
 *
 *  A fun little room that players can find near the Mercenary Guild.
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;
inherit "/d/Sparkle/area/tutorial/lib/herbsearch";

#include <filter_funs.h>   /* for FILTER_LIVE         */
#include <macros.h>        /* for QCTNAME             */
#include <stdproperties.h> /* for OBJ_I_CONTAIN_WATER */


/* Prototypes */
public void        create_merc_room();
public int         do_dive(string arg);
public void        init();
public int         climb_bridge(string arg);
public int         do_drink(string arg);
public string      exa_graffiti();


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("on a shallow bank tucked beneath a bridge");
    set_long("You are crouching beneath the timbers of a large and"
      + " sturdy bridge which spans the " + RIVERNAME + " River. The"
      + " waters of the river flow past directly at your feet to the"
      + " north of this shallow bank.\n");

    try_item( ({ "river", lower_case(RIVERNAME),
                 lower_case(RIVERNAME) + " river",
                 "river " + lower_case(RIVERNAME), "water",
                 "waters", "waters of the river", "river waters",
                 "waters of the " + lower_case(RIVERNAME) + " river" }),
        "The water flows somewhat noisily here where the large"
      + " foundations of the bridge rise out of the river.\n");
    try_item( ({ "bridge", "wooden bridge", "sturdy bridge",
                 "sturdy wooden bridge" }),
        "The bridge is extremely sturdy, having been constructed to"
      + " support the traffic of an active logging camp. The underside"
      + " of the bridge is a framework of large timbers which support"
      + " the weight of the overpass.\n");
    try_item( ({ "frame", "frame of the bridge" }),
        "Sturdy. Built to last!\n");
    try_item( ({ "camp", "mercenary camp", "logging camp",
                 "mercenary guild", "old logging camp", "guild" }),
        "You can't see much of it from here under the bridge.\n");
    try_item( ({ "road", "path" }),
        "The path is topside. You'll have to climb back up to get a"
      + " better view.\n");
    try_item( ({ "framework", "timber", "timbers", "large timber",
                 "large timbers", "framework of timbers",
                 "framework of large timbers", "underside",
                 "underside of the bridge" }),
        "These timbers have been milled by skilled hands and heavy"
      + " equipment. Erected to support an entire logging operation,"
      + " they can more than handle the foot traffic the bridge"
      + " experiences these days.\n");
    try_item( ({ "bank", "shallow bank", "river bank", "riverbank",
                 "bank of the river" }),
        "The bank of the river is extremely shallow here, extending"
      + " only a very short distance from the steep rise that makes its"
      + " way up to road level. The bank continues northwest following"
      + " the river upstream.\n");
    try_item( ({ "rise", "steep rise" }),
        "The bank of the river rises steeply, forming somewhat of a"
      + " wall south of the river.\n");
    try_item( ({ "wall", "south" }),
        "The riverbank to the south rises steeply back up to road"
      + " level, crowding this fairly narrow bank beneath the bridge.\n");
    try_item( ({ "foundation", "foundations", "large foundation",
                 "large foundations" }),
        "The foundations of the bridge are composed of huge blocks of"
      + " stone that have been quarried and then cut to fit together.\n");
    try_item( ({ "block", "blocks", "stone block", "stone blocks",
                 "huge block", "huge blocks", "block of stone",
                 "blocks of stone", "huge block of stone",
                 "huge blocks of stone" }),
        "You notice that someone has carved some graffiti into one of"
      + " the stone blocks.\n");
    try_item( ({ "graffiti" }), exa_graffiti);
    try_item( ({ "magic", "enchantment", "magical enchantment" }),
        "Very strange indeed.\n");
    try_item( ({ "overpass" }),
        "A great deal of traffic is handled by this bridge.\n");
    try_item( ({ "traffic", "foot traffic" }),
        "You'd not be able to see it unless someone hung their head"
      + " out over the rail. No one is doing so presently.\n");
    try_item( ({ "rail", "rail of the bridge" }),
        "The rail of the bridge prevents people from accidentally"
      + " falling into the river when drunk. Very important, you"
      + " know.\n");

    add_cmd_item( ({ "graffiti" }),
                  ({ "write", "engrave" }),
        "You struggle to write some graffiti on the huge stone block,"
      + " but there seems to be some sort of magical enchantment which"
      + " prevents it.\n");

    add_river_view();
    add_outdoor_view();

    add_prop(OBJ_I_CONTAIN_WATER, -1); /* infinite water here */

    add_exit("behind_mill", "northwest", 0, 1, 1);

    set_no_exit_msg( ({ "northwest", "north", "northeast", "east" }),
        "You pause at the waters edge, and decide against wading in.\n");
    set_no_exit_msg( ({ "southeast" }),
        "You walk a little ways downstream. Finding nothing of interest,"
      + " you return to stand beneath the bridge.\n");
    set_no_exit_msg( ({ "southwest", "south", "west" }),
        "The riverbank rises steeply, preventing your movement.\n");
    set_no_exit_msg( ({ "up" }),
        "Possible, probably, but you'll have to climb.\n");

    set_up_herbs( ({ "/d/Sparkle/common/herbs/cattails", }),
        ({ "ground", "bank", "water", "river" }), 3);

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
        
    if (!parse_command(arg, ({}),
        "[off] [of] [in] [into] [the] 'bank' / 'water' / 'river' / "))
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
    add_action(climb_bridge, "climb");
    add_action(do_drink, "drink");
} /* init */


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
        "[up] [to] [the] [top] [of] [the] [sturdy]"
      + " [wooden] 'bridge' / 'path'"))
    {
        if (arg == "up")
        {
            notify_fail("Climb up what?\n");
        }
        else
        {
            notify_fail("You don't seem to be able to climb there.\n");
        }
        return 0;
    }

    targets = FILTER_LIVE(all_inventory(this_object()));
    non_seers = filter(targets, not @ this_player()->check_seen);

    destination = safely_load_master_file(ROOM_DIR + "path2");

    write("You climb back to the top of the bridge.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " climbs up to"
      + " the top of the bridge.\n",
        non_seers + ({ this_player() }));

    targets = FILTER_LIVE(all_inventory(destination));
    non_seers = filter(targets, not @ this_player()->check_seen);

    tell_room(destination, QCTNAME(this_player()) + " arrives, climbing"
      + " up over the side of the bridge from below.\n",
        non_seers + ({ this_player() }));

    this_player()->move_living("M", destination, 1, 0);
    return 1;
} /* climb_bridge */


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
        "[from] [the] 'water' / 'river'"))
    {
        notify_fail("Drink from the river perhaps?\n");
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
        write("You scoop a handful of river water, and sip it"
            + " cautiously. It is icy cold, and very refreshing."
            + " You seem to have drunk your fill.\n");
    }
    else
    {
        write("You scoop a handful of river water, and sip it"
            + " cautiously. It is icy cold, and very envigorating."
            + " You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " stoops and drinks some water"
        + " from the river.\n");

    return 1;
} /* do_drink */


/*
 * Function name:        exa_graffiti
 * Description  :        show what the graffiti says, and if you
 *                       are a certain someone, explain a bit
 * Returns      :        string - the desc for the add_item
 */
public string
exa_graffiti()
{
    string desc = "The graffiti reads:\n\n\tThanks a ton Ilrahil!\n\n";

    if (this_player()->query_real_name() == "ilrahil")
    {
        desc += "Now, who would write a thing like that about you?"
          + " Perhaps all the effort you went to in helping with the"
          + " development of the Free Mercenary Guild was deeply"
          + " appreciated by someone.\n";
    }

    return desc;
} /* exa_graffiti */
