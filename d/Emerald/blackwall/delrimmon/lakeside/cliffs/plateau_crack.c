/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/plateau_crack.c
 * 
 *  This is the inside of a crack in one of the cliff walls high
 *  up among the peaks of the western slopes of the Blackwall Mountains which
 *  surround Del Rimmon in the Emerald Lands. A little stream flows
 *  into a hole in the ground here.
 *
 *  Copyright (c) March 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/stream";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_del_rimmon();
public string  describe();
public string  drink_stream();
public string  describe_stream_hook();
public string  notify_purification_hook();
public string  describe_opening();
public int     enter_opening(string arg);
public void    init();


/*
 * function name:        create_del_rimmon
 * description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_pure_water(1);
    add_name("high_cliffs");
    set_short("inside a crack in a rock wall");
    set_long(describe);

    add_stream_items();
    add_item( ({ "ground" }), BSN(describe_stream_hook()) );
    add_item( ({ "opening", "small opening", "dark opening",
                 "hole", "opening in the rock wall",
                 "opening in the rock walls", "small hole",
                 "dark hole" }), describe_opening);
    add_item( ({ "crack", "here", "area" }), BSN(
        "The crack recesses into the walls of rock, narrowing to"
      + " the south, where a small opening is visible in the darkness."
      + " To the north, a plateau is visible extending outward into"
      + " the bright air."));
    add_item( ({ "wall", "walls", "walls of rock", "rock walls",
                 "rock", "jagged rock", "jagged rock wall",
                 "jagged rock walls", "rock wall",
                 "wall of rock" }), BSN(
        "The walls of rock which define the sides of this recess"
      + " are jagged and dark. They narrow dramatically to the"
      + " south."));
    add_item( ({ "light", "light from the outside" }), BSN(
        "Light from the outside floods into this recess"
      + " from the outside, dimly illuminating the rock walls."));
    add_item( ({ "sky" }), BSN(
        "Though light enters this crack, the sky is not readily"
      + " visible from within the rock walls here."));
    add_item( ({ "outside", "plateau", "long plateau", "north" }), BSN(
        "To the north, a plateau extends away from this crack"
      + " in the rock, high in the peaks of the Blackwall Mountains."));

    add_prop(OBJ_I_CONTAIN_WATER, contain_water_vbfc);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
             "from a crack in the rock wall.");

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/high_ledge", "north");

    set_no_exit_msg( ({ "northeast", "east", "southeast", "south",
                        "southwest", "west", "northwest" }),
        "You immediately run up against jagged rock in that"
      + " direction.\n");
} /* create_del_rimmon */


/*
 * function name:        describe
 * description  :        provide a variable room description
 * returns      :        string -- the long description
 */
public string
describe()
{
    string  room_txt = "Inside a crack in a rock wall. Light from the"
                     + " outside pours in from the north, where the"
                     + " jagged rock walls open up onto a long"
                     + " plateau. The crack narrows sharply to the"
                     + " south ";

    if (Pure_Water)
    {
        room_txt += "where a stream of water flows down a small"
                  + " opening, to disappear in the darkness.";
    }

    else
    {
        room_txt += "where a small opening is visible in the darkness.";
    }

    return BSN(room_txt);
} /* describe */


/*
 * Function name: drink_stream
 * Description  : handles response should a player try to drink from
 *                the stream based on Pure_Water
 * Returns      : string message
 */
public string
drink_stream()
{
    if (Pure_Water)
    {
        return BSN("You stoop down and scoop some of the stream water"
             + " into your mouth. It is icy cold, and extremely"
             + " refreshing.");
    }

    else
    {
        return BSN("The stream bed is dry.");
    }
} /* drink_stream */



/*
 * function name:        describe_stream_hook
 * description  :        provides a unique description for the
 *                       stream in this room, based upon whether
 *                       or not the streambed is dry.
 * returns      :        string -- the stream description
 */
public string
describe_stream_hook()
{
    if (Pure_Water)
    {
        return     "A stream runs along a narrow channel in the"
                 + " ground here, disappearing through an opening"
                 + " in the darkness to the south.";
    }

    return     "A dry stream bed runs along the ground here,"
             + " leading to an opening in the darkness to the"
             + " south.";
} /* describe_stream_hook */


/*
 * function name:        notify_purification_hook
 * description  :        provides a unique message for when the stream
 *                       in this room is changed
 * returns      :        string -- the message
 */
public string
notify_purification_hook()
{
    if (!Pure_Water)
    {
        return "The stream suddenly dwindles to nothing, leaving"
             + " a dry streambed in the channel.";
    }

    return "The dry channel suddenly is filled with a flow of"
         + " water from the north, which runs the length of the"
         + " streambed to disappear into an opening in the darkness"
         + " to the south.";
} /* notify_purification_hook */


/*
 * function name:        describe_opening
 * description  :        provide an item description for the opening
 * returns      :        string -- the opening description
 */
public string
describe_opening()
{
    string opening_txt = "In the darkness to the south, a small"
                       + " opening is visible in the rock walls,"
                       + " near to the ground.";

    if (Pure_Water)
    {
        opening_txt += " A stream of water from the north empties"
                     + " into its depths.";
    }

    return BSN(opening_txt);
} /* describe_opening */


/*
 * function name:        enter_opening
 * description  :        allow the player to try to enter the opening
 * arguments    :        arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
enter_opening(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (!parse_command(arg, ({}),
        "[in] [into] [the] [dark] [small] 'opening' / 'hole'"
      + " [in] [the] [rock] [rocks] [wall] [walls] [to] [the]"
      + " [south]"))
    {
        return 0;
    }

    if (Pure_Water)
    {
        NFN0("The water which flows into the opening makes that"
           + " quite impossible.");
    }

    WRITE("With some difficulty, you crawl into the opening in the"
        + " rock walls.");
    say(QCTNAME(TP) + " crawls with some difficulty into an opening"
                    + " in the rock walls to the south.\n");
    TP->move_living("M", DELRIMMON_DIR + "lakeside/cliffs/crawlspace1", 1);
    say(QCTNAME(TP) + " arrives from the north, crawling through"
                    + " a hole.\n");

    return 1;
} /* enter_opening */


/*
 * function name:        init
 * description  :        add some verbs for the player
 */
public void
init()
{
    ::init();

    add_action(enter_opening, "enter");
    add_action(enter_opening, "crawl");
} /* init */
