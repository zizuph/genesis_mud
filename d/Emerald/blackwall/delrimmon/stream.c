/*
 *  /d/Emerald/blackwall/delrimmon/stream.c
 *
 *  This master is inherited by rooms along the lakeside of emyn
 *  muil containing a stream which has been defiled by the
 *  orcs. This file defines functions related to cleaning that
 *  stream, which is an option to the player.
 *
 *  Note: Inheriting this room requires that you redefine the mixed 
 *       global variable Next_Stream with the pathname of the
 *       room intended to be downstream from the inheriting room.
 *       Failing to do so will result in the end of the domino
 *       effect. (which we want to do eventually!)
 *
 *  Copyright (c) November 1997 by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <macros.h>    // for VBFC
#include <ss_types.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
string  Next_Stream;     /* pathname of downstream room */
string  Up_Room;         /* where to go if player climbs up chimney */
string  Down_Room;       /* where to go if player climbs down chimney */
int     Pure_Water = 0;  /* 0 = pure, 1 = defiled */

/* prototypes */
public void    add_stream_items();
public string  describe_stream_hook();
public void    add_chimney_items();
public string  chimney_desc();
public string  stream_txt();
public string  debris_txt();
public string  debris_cmd();
public string  drink_stream();
public string  notify_purification_hook();
public void    change_next_stream(int i);
public int     change_stream(int i);
public int     climb_chimney(string str);
public mixed   look_at_waterfall();
public int     contain_water_vbfc();

public void    set_uproom(string s) { Up_Room = s; }
public void    set_downroom(string s) { Down_Room = s; }
public void    set_pure_water(int i) { Pure_Water = i; }
public int     query_pure_water() { return Pure_Water; }


/*
 * function name:        add_stream_items
 * description  :        add some items for the stream
 */
public void
add_stream_items()
{
    TO->try_item( ({"stream", "streams", "water"}), VBFC("stream_txt") );
    TO->try_item( ({"debris", "foul-smelling debris"}),
        VBFC("debris_txt") );
    TO->try_item( ({"channel", "narrow channel"}), BSN(
        "The channel dug out by the stream is not deep, yet"
      + " makes a visible depression in the ground here."));
    TO->try_item( ({"depression", "visible depression"}), BSN(
        "Erosion from the stream has deepened the channel over the"
      + " years."));

    TO->add_cmd_item( ({"debris", "foul-smelling debris"}),
                  ({"search", "get"}), VBFC("debris_cmd") );
    TO->add_cmd_item( ({"stream", "streams", "channel", "narrow channel"}),
                  ({"search", "touch", "feel", "swim"}), BSN(
        "The water of the stream is icy cold, and numbs your flesh"
      + " as you touch it."));
//  TO->add_cmd_item( ({"stream", "streams", "from stream", "water",
//                  "water from stream"}),
//                ({"drink"}), VBFC("drink_stream") );
} /* add_stream_items */

/*
 * Function name: describe_stream_hook
 * Description  : redefine in inheriting rooms to change the description
 *                of the stream
 * Returns      : unique stream description (string)
 */
public string
describe_stream_hook()
{
    return "Running through a narrow channel in the ground, a stream"
         + " trickles swiftly along here.";
} /* describe_stream_hook */


/*
 * function name:        add_chimney_items
 * description  :        add some common items for the chimney
 */
public void
add_chimney_items()
{
   TO->try_item( ({ "water", "waterfall", "trickle",
                    "trickle of water" }), look_at_waterfall);
   TO->try_item( ({"erosion", "water erosion"}), BSN(
        "The chimney looks to have been carved out over many years"
      + " by the flow of water down the cliff side."));
   TO->try_item( ({"vent", "inner vent"}), BSN(
        "The inner surface of the chimney which extends up the rock"
      + " face is quite smooth, having been worn continuously by"
      + " falling water."));
   TO->try_item( ({"jagged edge", "edge of the chimney"}), BSN(
        "The edge of the chimney is jagged, due to its nature as"
      + " a literal cross section of the texture along the"
      + " cliffs which has been created by the cutting of the"
      + " waterfall."));
   TO->try_item( ({"texture", "cross section"}), BSN(
        "Where a chimney has been cut out of the cliffs, the"
      + " texture of the rock is jagged, creating what would"
      + " surely be perfect hand holds for a climber."));
   TO->try_item( ({"chimney"}), chimney_desc );

   TO->add_cmd_item( ({"chimney"}),
                  ({"search"}), BSN(
        "Examining the chimney more closely, you notice that the"
      + " texture of its sides is such that it would probably be"
      + " quite easy to climb."));
} /* add_chimney_items */


/*
 * Function name: chimney_desc
 * Description  : describes the chimney, and tells us if the waterfall
 *                is in action.
 * Returns      : description of the chimney (string)
 */
public string
chimney_desc()
{
    string  chdesc = "A chimney perhaps three feet in width has"
                   + " been bored out of the cliffside here.";

    if (query_pure_water())
    {
        chdesc += " A small waterfall courses down through the passage"
                + " in the rock to spill into a pool at the base of"
                + " the cliff.";
    }

    else
    {
        chdesc += " A tiny trickle of water winds and drips down the"
                + " length of the chimney, falling into a pool at the"
                + " base of the cliff.";
    }

    return BSN(chdesc + " The erosion from the water has left the"
                      + " inner vent of the chimney smooth, but"
                      + " created a jagged edge along both sides.");
} /* chimney_desc */


/*
 * Function name: stream_txt
 * Description  : uses whatever text is returned by
 *                describe_stream_hook, and adds to it a description
 *                of the cleanliness of the water.
 * Returns      : description of the stream (string)
 */
public string
stream_txt()
{
    string stream_desc = describe_stream_hook();

    if (!Pure_Water && !(TO->id("high_cliffs")) )
    {
        stream_desc += " The stream seems to have been somehow defiled,"
                    + " as it is dark and clouded with foul-smelling"
                    + " debris.";
    }

    return BSN(stream_desc);
} /* stream_txt */


/*
 * Function name: debris_txt
 * Description  : returns a description based on whether or not
 *                there are supposed to be debris in the stream
 *                based on Pure_Water.
 * Returns      : string message
 */
public string
debris_txt()
{
    if (Pure_Water)
        return BSN("You find no debris.");

    else return BSN("The debris flow past too quickly to"
              + " view closely. It is obvious, however, that they"
              + " are none too pleasant.");
} /* debris_txt */


/*
 * Function name: debris_cmd
 * Description  : identical to debris_txt, but meant forTO->add_cmd_item
 * Returns      : string message
 */
public string
debris_cmd()
{
    if (Pure_Water)
        return BSN("You find no debris.");

    else return BSN("The debris flow by so swiftly that it seems"
              + " impossible to get a closer look at them. Regardless,"
              + " you recognize them to be immediately unpleasant.");
} /* debris_cmd */


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
        return BSN("Just as you are about to swallow the icy cold water"
             + " from the stream, a foul stench hits your nose, and"
             + " you notice that the water has a dull brownish hue."
             + " Such water is unfit for consumption!");
    }
} /* drink_stream */


/*
 * Function name: notify_purification_hook
 * Description:   Redefine this hook to change the message given to
 *                players in a given room when the water is changed.
 */
public string
notify_purification_hook()
{
    if (!Pure_Water)
        return "The water of the stream runs suddenly foul, as a"
             + " fresh current from upstream turns the water"
             + " an unpleasant colour.";

    return "The water of the stream suddenly runs clear, as"
         + " a fresh current from upstream purifies the"
         + " water.";
} /* notify_purification_hook */


/*
 * Function name: change_next_stream
 * Description:   Called by an alarm in change_stream, this function
 *                calls change_stream in the object defined by the
 *                global variable Next_Stream, creating the domino
 *                effect we want. If Next_Stream is not defined, then
 *                we break the chain of alarms.
 * Arguments:     1 = purify, 0 = defile (default)
 */
public void
change_next_stream(int i)
{
    if (strlen(Next_Stream))
    {
        FIX_EUID;

        Next_Stream->change_stream(i);
    }
} /* change_next_stream */


/*
 * Function name: change_stream
 * Description:   This function tells players in a room text defined
 *                by nofiy_purification hook, and sets the Global
 *                Varable in the room - Pure_Water. It
 *                then sets a delay alarm to repeat the process.
 * Arguments:     1 = purify, 0 = defile (default)
 */
public int
change_stream(int i)
{
    set_pure_water(i);
    tell_room(TO, BSN(notify_purification_hook()) );

    set_alarm(3.0, 0.0, &change_next_stream(i));
    return 1;
} /* change_stream */


/*
 * function name:        climb_chimney
 * description  :        allow the player to try to climb up
 *                       the chimney in the rock, either up
 *                       or down
 * arguments    :        string str -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
climb_chimney(string str)
{
    string *dir = ({ "up", "down" });
    int     down_true;

    if (!TO->id("chimney_room"))
    {
        return 0;
    }

    if (!strlen(str))
    {
        NFN0("Where do you wish to climb?");
    }

    if (str == "up" || str == "down")
    {
        NFN0("What do you wish to climb " + str + "?");
    }

    if (parse_command(str, ({}),
        "[up] [down] [the] 'cliff' / 'cliffs' [side] [sides]"))
    {
        WRITE("The cliffs are far too difficult to climb, except"
           + " perhaps where a waterfall has carved a chimney"
           + " in the rock face nearby.");

        return 1;
    }

    if (parse_command(str, ({}),
        "[the] [narrow] [wide] 'chimney' / 'gap' / 'vent' /"
      + " 'waterfall'"))
    {
        NFN0("You must supply a direction when climbing.");
    }

    if (!parse_command(str, ({}),
        "%p [the] [narrow] [wide] 'chimney' / 'gap' / 'vent' /"
      + " 'waterfall'", dir))
    {
        return 0;
    }
        
    if (dir[0] == "up" && TO->id("chimney_top"))
    {
        NFN0("You already stand at the top of the chimney.");
    }

    if (dir[0] == "down" && TO->id("chimney_bottom"))
    {
        NFN0("You already stand at the bottom of the chimney.");
    }

    if (query_pure_water())
    {
        NFN0("The waterfall which flows down the chimney of rock"
           + " makes any attempt to climb that direction quite"
           + " unsuccessful.");
    }

    if (TP->query_fatigue() < (TP->query_max_fatigue() / 2) )
    {
        write("You are too tired to try that right now.\n");
        return 1;
    }

    if (TP->query_skill(SS_CLIMB) < 20 + random(5) )
    {
        NFN0("You grasp the sides of the chimney, and struggle"
           + " a few feet " + dir[0] + " the vent, but are soon" 
           + " at a loss as to where to find a good hand hold,"
           + " and decide not to tax your meager skills any"
           + " further.");
    }

    this_player()->reveal_me(1); /* sorry, can't hide while climbing */

    WRITE("Grasping firmly the handholds afforded by the chimney"
        + " in the rock, you make your way " + dir[0] + " the"
        + " side of the cliff face.");
    SAY(" climbs slowly " + dir[0] + " the side of the cliff,"
        + " navigating the narrow confines of a"
        + " chimney which has been bored out of the"
        + " cliff face by a waterfall.");

    TP->add_fatigue(-(TP->query_max_fatigue() / 2) );
    tell_room(((down_true = (dir[0] == "down")) ? Down_Room : Up_Room),
        QCTNAME(this_player()) + " arrives, climbing " + dir[0]
      + " the chimney in the rock.\n");
    TP->move_living("M",
        ((down_true = (dir[0] == "down")) ? Down_Room : Up_Room), 1);

    return 1;
} /* climb_chimney */


/*
 * function name:        look_at_waterfall()
 * description  :        provide a description of the waterfall, provided
 *                       the room contains the chimney
 * returns      :        string -- the waterfall desc
 */
public mixed
look_at_waterfall()
{
    if (TO->id("chimney_room"))
    {
        if (TO->query_pure_water())
        {
            return BSN("A great deal of water splashes down the"
                     + " length of the chimney in the form of a"
                     + " waterfall.");
        }

        return BSN("Water makes its way slowly down the length of"
                 + " the chimney in the form of a weak trickle.");
    }

    return 0;
} /* look_at_waterfall */


/*
 * Function name:        contain_water_vbfc
 * Description  :        we check if the stream contains water or not.
 * Returns      :        0 -- if no water, -1 -- if water.
 */
public int
contain_water_vbfc()
{
    if (Pure_Water)
    {
        return -1;
    }

    return 0;
} /* contain_water_vbfc */


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

    if (Pure_Water)
    {
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
    }

    write("Just as you are about to swallow the icy cold water"
     + " from the stream, a foul stench hits your nose, and"
     + " you notice that the water has a dull brownish hue."
     + " Such water is unfit for consumption!\n");

    return 1;
} /* do_drink */
