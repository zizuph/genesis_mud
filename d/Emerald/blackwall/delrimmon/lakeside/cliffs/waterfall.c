/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/waterfall.c
 *
 *  This is a place along the ledge of a plateau high up in the
 *  western ridges of the Blackwall Mountains. Runoff from a glacier
 *  to the west flows along the plateau in the form of a stream
 *  here. However, the stream has been diverted from its original
 *  course by a minor landslide here, and flows instead to the
 *  south, along the plateau. A player may dig out the original
 *  course of the stream with a shovel, restoring the flow of the
 *  waterfall over the edge. This is the source of the stream which
 *  runs through the forest below, to the lake.
 *
 *  Copyright (c) March 1999, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: December 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge_master";
inherit "/d/Emerald/blackwall/delrimmon/stream";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_ledge();
public int     clear_waterfall(string str);
public void    init();
public string  describe();
public string  notify_purification_hook();
public void    change_next_stream(int i);
public string  exa_boulders();
public string  describe_stream_hook();
public void    reset_room();


/*
 * function name:        create_ledge
 * description  :        create the room with area presets
 */
public void
create_ledge()
{
    Next_Stream = DELRIMMON_DIR + "lakeside/cliffs/ledge8";
    set_cliff_base(DELRIMMON_DIR + "lakeside/nw_cliff1");

    set_extraline(describe);
    set_downroom(DELRIMMON_DIR + "lakeside/cliffs/ledge8");
    add_name("chimney_room");
    add_name("chimney_top");
    add_name("high_cliffs");
    add_name("del_rimmon_cliffs");

    add_lakeview();
    add_chimney_items();
    add_stream_items();

    add_item( ({ "plateau" }), BSN(
        "Though very high above the lake, a plateau spreads out to"
      + " the west and south here, running fairly level beneath the"
      + " tall peaks."));
    add_item( ({ "north", "area to the north", "ledge to the north",
                 "northern ledge" }),
        "To the north, a ledge is visible curving slightly to the"
      + " east as it winds to frame the lake. It was probably once"
      + " possible to travel to that ledge from here, though now"
      + " boulders have fallen to block passage. An object of some"
      + " kind appears to be mounted on the ledge, but it is"
      + " difficult to see what it might be from here.\n");
    add_item( ({ "object", "object on the ledge" }),
        "The object on the ledge is too distant to recognize. It"
      + " gleams in the light, however, suggesting that it might"
      + " be made of some sort of metal.\n");
    add_item( ({ "west", "western glacier", "glacier",
                 "minor glacier" }), BSN(
        "A glacier is nestled between two tall peaks to the west, "
      + "its icy surface gleaming in the crisp mountain air."));
    add_item( ({ "surface", "icy surface", "snow", "compacted snow",
                 "snow and ice", "compacted snow and ice" }), BSN(
        "Compacted snow and ice form the surface of the glacier"
      + " to the west, which rests in the saddle of two tall peaks."));
    add_item( ({ "peaks", "tall peaks", "two peaks", "tall peak",
                 "peak", "two tall peaks", "saddle" }), BSN(
        "Two tall peaks rise to the west, where a glacier has formed"
      + " in this high rocky region."));
    add_item( ({ "boulder", "boulders", "debris", "rocky debris",
                 "pile", "pile of boulders", "course" }), exa_boulders);
    add_item( ({ "water", "runoff", "runoff water" }),
              VBFC("stream_txt") );
    add_item( ({ "rocks", "rock", "south" }), BSN(
        "There are many rocks along the plateau to the south."));
    add_item( ({ "edge", "edge of the cliff", "precipice",
                 "cliff", "cliffside", "edge of the plateau" }),
                 chimney_desc);

    add_cmd_item( ({ "boulder", "boulders", "large boulders",
                     "large boulder", "pile", "pile of boulders" }),
                  ({ "climb", "jump" }),
        "The boulders are very large, and unevenly piled. Attempting to"
      + " climb over them would be far too risky so close to a fatal"
      + " dropoff.\n");
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/high_ledge", "south");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/glacier", "west");

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "The plateau ends in a sheer drop that way.\n");
    set_no_exit_msg( ({ "northwest", "southwest" }),
        "The sheer slopes of a tall peak rise to defy your progress.\n");
    set_no_exit_msg( ({ "north" }),
        "The way is blocked by a large pile of boulders.\n");
} /* create_ledge */


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
        "[from] [the] 'water' / 'stream' [from] [the] [stream]"))
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
        write("You scoop a handful of water from the stream, and sip it"
            + " cautiously. It is icy cold, and very refreshing."
            + " You seem to have drunk your fill.\n");
    }
    else
    {
        write("You scoop a handful of water from the stream, and sip it"
            + " cautiously. It is icy cold, and very refreshing."
            + " You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " stoops and drinks some water"
        + " from the stream.\n");

    return 1;
} /* do_drink */


/*
 * function name:        clear_waterfall
 * description  :        allow the player to attempt to restore the
 *                       stream to its normal course, by digging
 *                       a path through the debris. a shovel is
 *                       required.
 * arguments    :        string str -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
clear_waterfall(string str)
{
    mixed   fail;
    object  obj;

    if (!strlen(str))
        NFN0("What do you want to " + query_verb() + "?");

    if (!(parse_command(str, all_inventory(TP),
        "[away] [out] 'rocks' / 'boulders' / 'boulder' / 'pile'"
      + " / 'waterfall' / 'water' / 'waterway' / 'debris'"
      + " 'with' [the] %o", obj)))
    {
        if (parse_command(str, ({}),
            "[away] [out] [the] 'rocks' / 'boulders' / 'boulder'"
          + " / 'pile' / 'waterfall' / 'water' / 'waterway'"
          + " / 'debris' 'with' [by] 'hand' / 'hands'"))
        {
            /* parse_command() failed */
            NFN0("You would need a shovel to do that.");
        }

        // parse_command() failed
        NFN0("What do you want to " + query_verb() + " with what?");
    }

    if (!(obj->id("shovel")))
    {
        WRITE("Your " + obj->short() + " doesn't seem to do much good"
          + " at all. What you need is a shovel.");
        return 1;
    }

    if (Pure_Water)
    {
        WRITE("It appears as if someone has already cleared the"
            + " boulders from the streambed, as the debris"
            + " have been dispersed beside the flowing water.");
        return 1;
    }

    write("Using your " + obj->short() + ", you labour to clear a path"
        + " in the debris which have diverted the path of the stream."
        + " After a few minutes, the slow trickle of water which"
        + " flows down the chimney in the cliff begins to grow,"
        + " as the stream reconnects with its old path.\n");
    say(QCTNAME(TP) + " digs a path in the debris which have diverted"
        + " the course of the stream, using " + TP->query_possessive()
        + " " + obj->short() + ". After a few minutes, the slow"
        + " trickle of water which flows down the chimney in the"
        + " cliff begins to grow, as the stream reconnects with its"
        + " old path.\n");
    set_alarm(2.0, 0.0, &change_stream(1));
    set_alarm(300.0, 0.0, reset_room);

    MANAGER->set_dug_waterfall(this_player(), "Yes");

    return 1;
} /* clear_waterfall */


/*
 * function name:        init
 * description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_chimney, "climb");
    add_action(clear_waterfall, "dig");
    add_action(clear_waterfall, "clear");
    add_action(clear_waterfall, "remove");
    add_action(clear_waterfall, "move");
    add_action(do_drink, "drink");
} /* init */


/*
 * function name:        describe
 * description  :        provides a description of this room, based on
 *                       whether or not the stream is dammed up.
 * returns      :        string -- the room description
 */
public string
describe()
{
    string  waterfall_desc;

    waterfall_desc = "Here, a plateau extends a fair distance to the"
                   + " west, where a minor glacier is visible"
                   + " nestled between two tall peaks. ";

    if (query_pure_water())
    {
        waterfall_desc += "A stream runs from the glacier to the edge of"
                 + " a cliff here, where it pours down a chimney"
                 + " which years of water erosion have carved in the"
                 + " rock face.";
    }

    else
    {
        waterfall_desc += "A stream runs from the glacier to the"
                   + " edge of the cliff here, where a pile of"
                   + " boulders has diverted its course, sending it"
                   + " south to disappear among the rocks.";
    }

    return waterfall_desc;
} /* describe */

/*
 * function name:        notify_purification_hook
 * description  :        provides a special room message for when the
 *                       status of the waterfall stream is changed
 * returns      :        string -- text for the change
 */
public string
notify_purification_hook()
{
    if (!Pure_Water)
    {
        return "A loose shelf of stone from a nearby rock wall gives way"
      + " suddenly, toppling into the path of the stream and"
      + " diverting its course away from the edge of the cliff,"
      + " to run south along the edge.";
    }

    return "Finding its former path, the water quickly begins to flow"
         + " over the edge of the cliff, cascading down the length"
         + " of a chimney in the rock.";
} /* notify_purification_hook */

/*
 * Function name: change_next_stream
 * Description:   Called by an alarm in change_stream, this function
 *                calls change_stream in the object defined by the
 *                global variable Next_Stream, creating the domino
 *                effect we want. If Next_Stream is not defined, then
 *                we break the chain of alarms. Here, we redefine it
 *                so that we can trigger two streams instead of just
 *                one.
 * Arguments:     1 = purify, 0 = defile (default)
 */
public void
change_next_stream(int i)
{
    if (strlen(Next_Stream))
    {
        FIX_EUID;

        Next_Stream->change_stream(i);

        Next_Stream = DELRIMMON_DIR + "lakeside/cliffs/high_ledge";
        Next_Stream->change_stream( (i == 1) ? 0 : 1 );

        Next_Stream = DELRIMMON_DIR + "lakeside/cliffs/ledge8";
    }
} /* change_next_stream */

/*
 * function name:        exa_boulders
 * description  :        provides a description of the debris which
 *                       may or may not be blocking the stream here
 * returns      :        string -- the description
 */
public string
exa_boulders()
{
    if (!Pure_Water)
    {
        return BSN("A large pile of boulders and debris has apparently"
                 + " fallen across the path of the original stream"
                 + " bed, forcing the water to flow south along the"
                 + " plateau, rather than over the edge of the cliff. It"
                 + " appears as if the boulders have completely blocked"
                 + " off any northward movement along the ledge from"
                 + " here.");
    }

    return BSN("A large pile of boulders and debris lies beside a"
            + " narrow channel in the ground, where water flows"
            + " swiftly over the edge of the cliff. It appears as if"
            + " the boulders have completely blocked off any northward"
            + " movement along the ledge from here.");

} /* exa_boulders */

/*
 * function name:        describe_stream_hook
 * description  :        provides a unique description for the stream
 *                       in this room, dependant upon whether or not
 *                       debris have altered the course of the water
 * returns      :        string -- the description
 */
public string
describe_stream_hook()
{
    if (!Pure_Water)
    {
        return "A stream of runoff water from the western glacier flows"
             + " along the plateau here. A pile of boulders has fallen"
             + " across its original path, diverting the water to the"
             + " south, where it disappears among the rocks.";
    }

    return "A stream of runoff water from the western glacier flows"
         + " along the plateau here. Where it reaches the edge of"
         + " the cliff, if flows down a chimney in the rock which"
         + " has apparently been carved from the stone by many"
         + " years of erosion.";
} /* describe_stream_hook */

/*
 * function name:        reset_room
 * description  :        on resets, we want to again cause the stream
 *                       to be diverted in its course
 */
public void
reset_room()
{
    if (Pure_Water)
    {
        change_stream(0);
    }

    return;
} /* reset_room */
