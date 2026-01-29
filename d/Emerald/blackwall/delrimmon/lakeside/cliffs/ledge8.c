/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge8.c
 *
 *  The ledge along the western cliffs of the Blackwall Mountains
 *  winds in a northeast-southwest manner here. A waterfall from the
 *  glacial runoff has cut through the ledge here, forming a chimney
 *  in the rock, which skilled players may climb up or down. To continue
 *  along the ledge, one must jump over the gap heading south.
 *
 *  Copyright (c) August 1997, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge_master.c";
inherit "/d/Emerald/blackwall/delrimmon/stream";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_ledge();
public int     ledge_gap();
public string  room_describe();
public string  chimney_desc();
public string  notify_purification_hook();
public int     ledge_jump(string arg);
public void    init();
public string  notify_purification_hook();

/*
 * Function name: create_ledge
 * Description  : allows us to create the room with area presets
 */
public void
create_ledge()
{
    set_cliff_base(DELRIMMON_DIR + "lakeside/nw_cliff1");
    Next_Stream = DELRIMMON_DIR + "lakeside/nw_cliff1";

    set_uproom(DELRIMMON_DIR + "lakeside/cliffs/waterfall");
    set_downroom(DELRIMMON_DIR + "lakeside/nw_cliff1");

    set_extraline(room_describe);
    add_name("chimney_room");

    add_chimney_items();
    add_item( ({ "gap", "large gap", "gap in the ledge",
                 "large gap in the ledge" }), chimney_desc);

    add_prop(OBJ_I_CONTAIN_WATER, contain_water_vbfc);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge9","north");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge7", "southwest",
             ledge_gap, 1, 1);

    set_no_exit_msg( ({ "northeast", "east", "southeast", "south" }),
        "The ledge drops off there, and the fall would surely be the"
      + " death of you.\n");
    set_no_exit_msg( ({ "west", "northwest" }),
        "The walls of the cliffs rise to block movement in that"
      + " direction.\n");
} /* create_ledge */

/*
 * Function name: ledge_gap
 * Description  : sends a message to the player telling them that they
 *                cannot simply walk over thin air, preventing the
 *                success of the move from add_exit
 * Returns      : string -- message that the player cannot walk that dir
 */
public int   
ledge_gap()
{
    WRITE("A large section of the ledge has been carved away by"
        + " the same process which must have carved the chimney"
        + " in the side of the cliff. You cannot simply walk"
        + " in that direction.");

    return 1;
} /* ledge_gap */

/*
 * Function name: room_describe
 * Description  : allows us to modify the room description based on
 *                whether or not the water is clean.
 * Arguments    : none
 * Returns      : the text for the room description (string)
 */
public string
room_describe()
{
    string  rdesc;

    rdesc = "A ledge extends along the sides of the cliffs here,"
          + " winding its way in a gradual north-south direction."
          + " A chimney has been carved in the rock of the cliff,"
          + " creating a large gap in the ledge as it runs"
          + " directly to the southwest. ";

    if (Pure_Water)
    {
        rdesc += "A small waterfall splashes down the side of the"
              + " cliffs here, coursing through the chimney and"
              + " the gap in the ledge.";
    }

    else
    {
        rdesc += "A tiny trickle of water drips down the side of"
               + " the cliffs here, weakly disappearing through"
               + " the gap in the ledge.";
    }

    return rdesc;
}

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
                   + " been bored out of the cliffside here. It"
                   + " has cut through the ledge to the southwest.";

    if (query_pure_water())
    {
        chdesc += " A small waterfall courses down through the passage"
                + " in the rock.";
    }

    else
    {
        chdesc += " A tiny trickle of water winds and drips down the"
                + " length of the chimney, falling through a gap"
                + " in the ledge to the southwest.";
    }

    return BSN(chdesc + " The erosion from the water has left the"
                      + " inner vent of the chimney smooth, but"
                      + " created a jagged edge along both sides.");
} /* chimney_desc */


/*
 * function name:        ledge_jump
 * description  :        let the player try to jump over the ledge
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
ledge_jump(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[over] [across] [the] [large] [wide] "
      + "'gap' / 'chimney' / 'southwest' / 'sw' [in] [the] [ledge]"))
    {
        return 0;
    }

    WRITE("Taking a running jump, you leap across the gap in the"
        + " ledge to land on the opposite side.");
    say(QCTNAME(TP) + " takes a running jump and leaps across the"
        + " gap in the ledge to land on the other side.\n");

    TP->add_fatigue(-(30 + random(10)) );
    TP->move_living("M", DELRIMMON_DIR + "lakeside/cliffs/ledge7", 1);
    say(QCTNAME(TP) + " arrives, sailing over the gap from the northeast"
                    + " to land hard on the ledge here.\n");
    return 1;
} /* ledge_jump */

/*
 * function name:        init
 * description  :        add some verbs to the player
 */
public void
init()
{
    ::init();

    add_action(climb_chimney, "climb");
    add_action(ledge_jump, "jump");
    add_action(ledge_jump, "leap");
} /* init */


/*
 * Function name: notify_purification_hook
 * Description  : by redefining this, we give the room a unique message
 *              : when change_stream is called
 * Returns      : the unique text message (string)
 */
public string
notify_purification_hook()
{
    if (!Pure_Water)
    {
        return "The gushing flow of the waterfall dwindles to"
             + " a mere trickle, which continues to wind its"
             + " way feebly down the shaft of the chimney.";
    }

    return "The trickle of water which runs down the cliff face"
         + " splashes suddenly, becoming a rushing torrent"
         + " of water from above.";
} /* notify_purification_hook */
