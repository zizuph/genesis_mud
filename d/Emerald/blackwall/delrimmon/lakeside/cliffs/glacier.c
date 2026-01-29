/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/glacier.c
 *
 *  A glacier is nestled in the saddle between two high peaks along
 *  the western slopes of the Blackwall Mountains here. Its runoff winds
 *  down the cliffs to the east to eventually join with the waters of
 *  Del Rimmon.
 *
 *  Copyright (c) March 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/stream";

#include <macros.h>      /* for VBFC, etc */
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_del_rimmon();
public string  describe_stream_hook();
public int     make_snowball(string arg);
public void    init();

public mixed   get_snowball(string arg);

/*
 * function name:        create_del_rimmon
 * description  :        set up the room with domain presets
 */
public void
create_del_rimmon()
{
    set_loc(4);
    set_side("west");
    set_show_area_desc();
    set_pure_water(1);
    add_name("high_cliffs");
    add_name("del_rimmon_cliffs");

    set_short(del_rimmon_short);
    set_long(del_rimmon_long);

    set_extraline("A glacier rises majestically to the west, nestled"
                + " between the spires of two high peaks. Here, at its"
                + " feet, a stream of runoff from the melting snow"
                + " and ice flows away to the east, towards the edge"
                + " of a cliff.");

    add_view();
    add_lakeview();
    add_stream_items();
    add_item( ({ "runoff", "stream of runoff" }), VBFC("stream_txt") );
    add_item( ({ "glacier", "medium sized glacier", "west"}), BSN(
        "A glacier towers above you here, rising to the west where"
      + " it lies nestled in the saddle of two tall peaks."));
    add_item( ({ "saddle", "peak", "peaks", "two tall peaks",
                 "two peaks", "tall peak", "tall peaks", "spire",
                 "spires" }), BSN(
        "Two tall peaks loom to the west, where a glacier has formed"
      + " over many centuries of snow and ice to rest in the saddle"
      + " between them."));
    add_item( ({ "snow", "ice", "snow and ice", "melting snow",
                 "melting ice", "melting snow and ice" }), BSN(
        "The glacier is comprised mostly of hard ice, which has been"
      + " covered by a layer of compacted snow. Runoff from the"
      + " glacier flows to the east in the form of a stream."));
    add_item( ({ "hard ice", "compacted snow" }), BSN(
        "Many many years of accumulation would be required to achieve"
      + " a glacier of this size."));
    add_item( ({ "bed", "beds", "rock bed", "rock beds",
                 "high rock bed", "high rock beds" }), BSN(
        "Two peaks rise to the east, where a glacier has formed"
      + " betwixed their rock beds."));
    add_item( ({ "edge", "cliff", "edge of a cliff", "cliff edge",
                 "east" }), BSN(
        "A ways to the east, the edge of a cliff can be glimpsed"
      + " between a cleft in a rock wall which separates the glacier"
      + " from the precipice."));
    add_item( ({ "cleft", "rock wall", "wall" }), BSN(
        "The cleft in the wall to the east seems to have been eroded"
      + " away by the constant flow of the runoff from the glacier"
      + " here."));

    add_cmd_item( ({ "snow", "ice", "glacier", "peak", "peaks",
                     "saddle" }),
                  ({ "climb" }), BSN(
        "The glacier is far too steep to climb."));
    add_cmd_item( ({ "snow", "compacted snow" }),
                  ({ "get", "take" }), BSN(
        "There is far too much snow to take with you. You might be"
      + " able to make a snowball, however."));

    add_prop(OBJ_I_CONTAIN_WATER, -1);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/waterfall", "east");

    set_no_exit_msg( ({ "north", "northeast", "southeast", "south",
                        "southwest", "northwest" }),
        "Sheer rock slopes block your progress.\n");
    set_no_exit_msg( ({ "west" }),
        "You are unable to climb further up the glacier.\n");
} /* create_del_rimmon */

/*
 * function name:        describe_stream_hook
 * description  :        we provide a unique description for the
 *                       stream in this room here
 * returns      :        string -- the stream desc
 */
public string
describe_stream_hook()
{
    return "The runoff from the glacier trails off to the east in"
         + " the form of a swiftly flowing stream, which has dug out"
         + " a narrow channel in the ground.";
} /* describe_stream_hook */


/*
 * function name:        make_showball
 * description  :        hey there is snow here, right?
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
make_snowball(string arg)
{
    object  snowball;

    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (!parse_command(arg, ({}),
        "[a] 'snowball' [out] [of] [with] [the] [snow] [glacier]"))
    {
        return 0;
    }

    WRITE("Scooping up some snow from the glacier, you form it into"
        + " a perfect snowball.");
    say(QCTNAME(TP) + " stoops and makes a snowball from the snow of"
                    + " the glacier.\n");

    snowball = clone_object(DELRIMMON_DIR + "obj/snowball")->move(TP);
    return 1;
} /* make_snowball */


/*
 * function name:        init
 * description  :        add some verbs for the player
 */
public void
init()
{
    ::init();

    add_action(make_snowball, "make");
    add_action(make_snowball, "create");
    add_action(make_snowball, "form");
    add_action(get_snowball, "get");
    add_action(get_snowball, "take");
} /* init */


/*
 * function name:        get_snowball
 * description  :        give the players a hint, but force them to
 *                       actually make the snowball if they want one
 * arguments    :        string arg -- what the player typed
 * returns      :        int 0
 */
public int
get_snowball(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    if (arg != "snowball" || arg != "snowballs")
    {
        return 0;
    }

    NFN0("There is lots of snow here, but no snowballs. If you want one,"
       + " you will have to make it yourself.");
} /* get_snowball */
