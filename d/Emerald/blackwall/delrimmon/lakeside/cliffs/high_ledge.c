/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/high_ledge.c
 *
 *  This ledge rests high atop the cliffs of the Blackwall Mountains
 *  to the west of the lake of Del Rimmon. A plateau extends to the
 *  north, and stream runs along the rocks here to disappear into a
 *  crack in the stone to the south.
 *
 *  Copyright (c) ?? 1998 ?? by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: December 2000
 */
#pragma strict_types;

inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge_master";
inherit "/d/Emerald/blackwall/delrimmon/stream";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_ledge();
public string  describe();
public string  drink_stream();
public string  describe_stream_hook();
public string  notify_purification_hook();
public string  exa_crack();
public int     enter_crack(string arg);
public void    init();


/*
 * function name:        create_ledge
 * description  :        allows us to set up the room with area presets
 */
public void
create_ledge()
{
    Next_Stream = DELRIMMON_DIR + "lakeside/cliffs/plateau_crack";
    set_cliff_base(DELRIMMON_DIR + "lakeside/w_cliff5");

    set_extraline(describe);

    set_pure_water(1);
    add_name("high_cliffs");
    add_name("del_rimmon_cliffs");
    add_stream_items();

    add_item( ({ "crack", "opening", "crack in the rock wall",
                 "dark crack", "crack in the rock",
                 "crack in the wall" }), exa_crack);
    add_item( ({ "wall", "rock wall", "south" }), BSN(
        "The plateau comes to an end to the south, where a rock wall"
      + " rises high above. A crack has formed in its base."));
    add_item( ({ "base", "base of the rock wall" }), BSN(
        "A stream bed runs up to the base of the rock wall where a"
      + " dark crack has formed."));
    add_item( ({ "bed", "stream bed", "streambed",
                 "dry stream bed", "dry streambed" }),
        BSN(describe_stream_hook()));
    add_item( ({ "plateau", "here" }), BSN(
        "This plateau spreads out to the north, where it travels"
      + " further westward towards the base of two tall peaks. It"
      + " is interrupted to the south by a rock wall."));
    add_item( ({ "tall peak", "peak", "peaks", "two peaks",
                 "two tall peaks", "tall peaks" }), BSN(
        "Two tall peaks rise to the northwest. A minor glacier is"
      + " visible nestled at their base."));
    add_item( ({ "glacier", "minor glacier", "base of the peaks" }),
    BSN("The glacier to the northwest may be the source of the"
      + " stream which courses along the ground here."));
    add_item( ({ "ground" }), BSN(describe_stream_hook()) );

    add_prop(OBJ_I_CONTAIN_WATER, contain_water_vbfc);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/waterfall", "north");

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "A sheer drop from the edge of the cliffs lies that way.\n");
    set_no_exit_msg( ({ "south" }),
        "Walls of rock block your progress in that direction. A large"
      + " crack in the rock looks large enough to enter, however.\n");
    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
        "The rocky slopes of a tall peak block your progress.\n");
} /* create_ledge */


/*
 * function name:        describe
 * description  :        provides a variable room description
 *                       depending on whether or not the stream
 *                       is here or not.
 * returns      :        string -- the room description
 */
public string
describe()
{
    string room_desc = "A plateau spreads out here high above the"
                     + " forest and lake to the east. Many rocks"
                     + " and boulders lie strewn about, ";

    if (Pure_Water)
    {
        room_desc += "surrounding a stream which flows in a narrow"
                   + " channel from the north, disappearing into a"
                   + " deep crack along a rock wall to the south.";
    }

    else
    {
        room_desc += "surrounding a dry channel which runs along"
                   + " the ground to disappear into a deep crack"
                   + " along a rock wall to the south.";
    }

    return room_desc;
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
                 + " ground here, disappearing through a crack"
                 + " in a rock wall to the south.";
    }

    return     "A dry stream bed runs along the ground here,"
             + " leading to a crack along a rock wall to the"
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
         + " streambed to disappear into a crack in the rock wall"
         + " to the south.";
} /* notify_purification_hook */


/*
 * function name:        exa_crack
 * description  :        provide a description for the crack in the
 *                       wall of rock to the south
 * returns      :        string -- the description
 */
public string
exa_crack()
{
    if (Pure_Water)
    {
        return BSN("The crack in the rock wall to the south appears"
                 + " to be wide enough for the average person to"
                 + " fit inside. A stream disappears into its depths.");
    }

    return BSN("The crack in the rock wall to the south appears"
             + " to be wide enough for the average person to fit"
             + " inside. A dry stream bed runs up to its opening.");
} /* exa_crack */


/*
 * function name:        enter_crack
 * description  :        allow the player to attempt to enter the
 *                       crack
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
enter_crack(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Enter what?");
    
    }

    if (!parse_command(arg, ({}),
        "[the] [dark] 'crack' / 'opening'"))
    {
        return 0;
    }

    TP->move_living("into a crack to the south",
                    DELRIMMON_DIR + "lakeside/cliffs/plateau_crack", 1);
    return 1;
} /* enter_crack */

/*
 * function name:        init
 * description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(enter_crack, "enter");
} /* init */
