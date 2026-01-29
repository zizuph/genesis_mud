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
#include <ss_types.h>      /* for SS_ACROBAT          */
#include <stdproperties.h> /* for OBJ_I_CONTAIN_WATER */
#include <time.h>          /* for TIME2FORMAT         */


/* Prototypes */
public void        create_merc_room();
public void        init();
public int         try_climb(string arg);
public int         ride_wheel(string arg);
public int         do_drink(string arg);
public int         do_dive(string arg);


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("beside a large turning waterwheel behind the mill");
    set_long("You stand on the riverbed beside a huge waterwheel which"
      + " turns endlessly with the flowing water of the river. Behind"
      + " you to the southwest, the riverbank rises up to support the"
      + " old mill, which towers above you.\n");
     

    try_item( ({ "river", lower_case(RIVERNAME),
                 lower_case(RIVERNAME) + " river",
                 "river " + lower_case(RIVERNAME), "water",
                 "waters", "waters of the river", "river waters",
                 "waters of the " + lower_case(RIVERNAME) + " river",
                 "stream" }),
        "The river flows beside the mill here, powering the water wheel"
      + " which dominates the riverbank to the northwest.\n");
    try_item( ({ "ground", "grass", "lawn", "down" }),
        "The ground is wet and muddy here along the river.\n");
    try_item( ({ "bridge", "wooden bridge", "sturdy bridge",
                 "sturdy wooden bridge", "southeast" }),
        "The bridge is visible to the southwest where it spans the"
      + " river you are standing beside.\n");
    try_item( ({ "mud", "dirt" }),
        "The mud is stewn with numerous pebbles.\n");
    try_item( ({ "pebble", "pebbles", "stone", "stones", "rock",
                 "rocks", "river stone", "river stones" }),
        "These are the sort of river stones that are often collected"
      + " by young children. They have been washed smooth over the many"
      + " years.\n");
    try_item( ({ "frame", "frame of the bridge" }),
        "Sturdy. Built to last!\n");
    try_item( ({ "camp", "mercenary camp", "logging camp",
                 "mercenary guild", "old logging camp", "guild" }),
        "You can't see much of it from here. The steep bank and"
      + " the mill block all view to the south.\n");
    try_item( ({ "road", "path", "paths", "roads" }),
        "They aren't visible from down here beside the river.\n");
    try_item( ({ "bank", "shallow bank", "river bank", "riverbank",
                 "bank of the river", "riverbed", "area" }),
        "The bank of the river is extremely steep and rises all"
      + " along the water on both shores. The riverbed proceeds"
      + " southeast back toward the bridge.\n");
    try_item( ({ "shore", "shores" }),
        "The shores of the river are very shallow, but do allow passage"
      + " in limited areas.\n");
    try_item( ({ "limited area", "limited areas" }),
        "Like right here, for instance.\n");
    try_item( ({ "rise", "steep rise" }),
        "The bank of the river rises steeply, forming somewhat of a"
      + " wall south of the river.\n");
    try_item( ({ "wall", "south" }),
        "The riverbank to the south rises steeply back up to camp"
      + " level, crowding this fairly narrow bank behind the mill.\n");
    try_item( ({ "mill", "old mill", "lumber mill", "sawmill",
                 "saw mill", "sawmill", "old saw mill", "old sawmill" }),
        "The old sawmill looms over the riverbed to the south, where"
      + " it rises from the steep bank. Its waterwheel juts out into"
      + " the stream, where it is turned by the endless flow of the"
      + " river.\n");
    try_item( ({ "roof", "roof of the mill" }),
        "You can't see much from down here. You notice that the"
      + " waterwheel extends a bit above it at its highest point.\n");
    try_item( ({ "wheel", "water wheel", "waterwheel", "large wheel",
                 "large waterwheel", "large water wheel", "turning wheel",
                 "turning water wheel", "turning waterwheel",
                 "large turning wheel", "large turning waterwheel",
                 "large turning water wheel" }),
        "The waterwheel is extremely impressive. Though rather old, it"
      + " continues to turn with no signs of disrepair as the waters of"
      + " the river push its many troughs on their circular journey from"
      + " the riverbed to high above the roof of the mill before they"
      + " start their journey downward again.\n");
    try_item( ({ "trough", "troughs", "many troughs",
                 "troughs of the waterwheel", "troughs of the wheel",
                 "troughs of the water wheel" }),
        "The troughs trap the water as it tries to flow under the wheel,"
      + " and are pushed forward and up as the wheel turns in response. You"
      + " notice a few leaves and other debris riding the troughs up and"
      + " over the top of the wheel as the process plays itself out in"
      + " a thousand similar variations every hour.\n");
    try_item( ({ "leaf", "leaves", "debris", "other debris" }),
        "They ride the wheel up to the top of the roof before they are"
      + " tossed back into the river on their way back down.\n");

    add_river_view();
    add_outdoor_view();

    add_prop(OBJ_I_CONTAIN_WATER, -1); /* infinite water here */

    add_exit("under_bridge", "southeast", 0, 1, 1);

    set_no_exit_msg( ({ "north", "northeast", "east" }),
        "You pause at the waters edge, and decide against wading in.\n");
    set_no_exit_msg( ({ "southwest", "south" }),
        "The riverbank rises steeply, preventing your movement.\n");
    set_no_exit_msg( ({ "northwest" }),
        "The waterwheel is in the way.\n");
    set_no_exit_msg( ({ "up" }),
        "Up? How?\n");

    set_up_herbs( ({ "/d/Sparkle/common/herbs/cattails", }),
        ({ "ground", "bank", "water", "river" }), 3);

    setuid();
    seteuid(getuid());
} /* create_merc_room */


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
    add_action(do_drink, "drink");
    add_action(try_climb, "climb");
    add_action(ride_wheel, "ride");
    add_action(ride_wheel, "grab");
    add_action(ride_wheel, "grasp");
    add_action(ride_wheel, "hold");
    add_action(ride_wheel, "grip");
    add_action(ride_wheel, "hang");
} /* init */


/*
 * Function name:        try_climb
 * Description  :        let players try to climb stuff
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
try_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (arg == "up")
    {
        notify_fail("Climb up what?\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [the] [water] 'wheel' / 'waterwheel'"))
    {
        notify_fail("Climb it? Hmmm ... looks dubious. Perhaps there is"
          + " another approach.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [the] [steep] [river] 'bank'"))
    {
        notify_fail("There are no good handholds, and it is too"
          + " slippery.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [to] [the] [old] 'mill' / 'roof'"))
    {
        notify_fail("The mill is out of reach here. The only part of"
          + " it within reach is the waterwheel.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [the] 'trough' / 'troughs' [of] [the] [waterwheel]"))
    {
        notify_fail("The troughs are in motion, passing by you on"
          + " their way up to the top of the waterwheel. You certainly"
          + " can't climb them, but you might be able to try to grab"
          + " one for a ride.\n");
        return 0;
    }

    notify_fail("You don't seem to be able to climb that.\n");
    return 0;
} /* try_climb */


/*
 * Function name:        ride_wheel
 * Description  :        allow players to climb under the bridge
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
ride_wheel(string arg)
{
    mixed  *targets;
    mixed  *non_seers;
    object  trough;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[on] [to] [onto] [in] [the] 'trough' / 'troughs' [of] [the]"
      + " [water] [wheel] [waterwheel]"))
    {
        if (parse_command(arg, ({}),
            "[on] [to] [onto] [in] [the] [water] 'waterwheel'"
          + " / 'wheel'"))
        {
            if (query_verb() == "ride")
            {
                notify_fail("That might be possible. How would you do it,"
                  + " though? You'd probably need to grab on to part of it"
                  + " or something.\n");
                return 0;
            }

            notify_fail("Be more specific. What part of the waterwheel do"
              + " you want to try to " + query_verb() + " on to?\n");
            return 0;
        }

        if (parse_command(arg, ({}),
            "[up] [to] [the] [old] 'mill' / 'roof'"))
        {
            notify_fail("The mill is out of reach here. The only part of"
              + " it within reach is the waterwheel.\n");
            return 0;
        }

        notify_fail("You don't seem to be able to " + query_verb()
          + " that.\n");
        return 0;
    }

    if (this_player()->query_skill(SS_ACROBAT) < 20)
    {
        write("You grab the edge of one of the troughs as it passes"
          + " by you and manage to hold on for a few seconds."
          + " Unfortunately, your acrobatic skills are so poor that"
          + " you are quickly off balance, and slip down to fall into"
          + " the shallow water with a loud splash!\n");

        this_player()->reveal_me();

        tell_room(this_object(),
            "A loud splash sounds out nearby, and you look around to"
          + " see " + QTNAME(this_player()) + " sitting waist-deep in"
          + " the shallow waters just off the bank, peering ruefully up"
          + " at the waterwheel.\n", this_player());

        write_file(LOG_DIR + "waterwheel",
            TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_real_name()) 
          + " couldn't ride - low acrobat skill.\n");

        return 1;
    }

    targets = FILTER_LIVE(all_inventory(this_object()));
    non_seers = filter(targets, not @ this_player()->check_seen);

    write("You deftly grab the edge of one of the troughs as it passes"
      + " by you and, clinging to it with all you are worth, begin"
      + " a slow arcing ascent toward the roof of the mill. Whoa this is"
      + " a bit tricky!\n");
    tell_room(this_object(), QCTNAME(this_player()) + " begins riding"
      + " the waterwheel, ascending along its slow arc toward the"
      + " top of the mill!\n", non_seers + ({ this_player() }));

    trough = clone_object(ROOM_DIR + "waterwheel");

    this_player()->move_living("M", trough, 1, 1);
    return 1;
} /* ride_wheel */


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
 * Function name:        add_outdoor_tells
 * Description  :        mask the inherited one to provide unique
 *                       tells for this room
 */
public void
add_outdoor_tells()
{
    add_tell("The waterwheel turns peacefully, spilling water back"
      + " into the river.\n");
    add_tell("The sounds of the river echo along the bank.\n");
    add_tell("A few leaves float by.\n");
    add_tell("A few birds fly overhead, passing out of sight behind"
      + " the roof of the mill.\n");
} /* add_outdoor_tells */