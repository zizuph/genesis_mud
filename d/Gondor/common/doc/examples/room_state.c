/*
 * /d/Gondor/common/doc/examples/room_state.c
 *	-- an example room that shows how to change the state
 *	   of something in the room (e.g., raise/lower lever),
 *	   and how to use VBFC to reflect the state in the
 *	   room and item descriptions.
 *
 * Created by Gnadnar 28-May-1998
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>	/* for ROOM_I_INSIDE */
#include "/d/Gondor/defs.h"

static int	Lever_is_up;	/* true if lever is up */

/* prototypes in order of appearance */
public void	create_gondor();
public void	reset_room();
public void	init();
public string	look_at(string arg);
public int	mess_with_lever(string arg);

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("a test room");
    set_long(&look_at("room"));
    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({ "floor", "wooden floor", "dust" }),
	BSN("The wooden floor is bare of all but dust."));
    add_item( ({ "east wall", "south wall", "west wall" }),
	BSN("The wall is bare and somewhat dirty."));
    add_item( ({ "wall", "walls" }),
	BSN("The walls are none too clean. Except for the lever " +
	    "on the north wall, they are bare."));
    add_item( ({ "north wall" }),
	&look_at("wall"));
    add_item( ({ "sturdy wooden lever", "sturdy lever",
	"wooden lever", "lever", }),
	&look_at("lever"));
    add_item( ({ "ceiling" }),
	BSN("The ceiling sags alarmingly. It looks as if it " +
	    "might fall at any moment."));

    reset_room();
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	raise the lever again
 *
 * You don't have to do this, of course.  It might make sense
 * just to leave the lever alone unless mortals change it,
 * in which case you don't need reset_room().
 */
public void
reset_room()
{
    ::reset_room();
    Lever_is_up = 1;
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add lever verbs
 */
public void
init()
{
    ::init();
    /* for purposes of this example, we only deal with "raise"
     * and "lower".  for real code, you'd want to handle "push",
     * "pull", "move", etc
     */
    add_action(mess_with_lever, "raise");
    add_action(mess_with_lever, "lower");
} /* init */


/*
 * Function name:	look_at
 * Description	:	vbfc for various descriptions
 * Arguments	:	string arg -- "room", "wall" or "lever"
 * Returns	:	string -- the description
 */
public string
look_at(string arg)
{
    string	desc,
		state;

    state = (Lever_is_up ? "raised" : "lowered");

    switch(arg)
    {
    case "room":
    	desc = "Except for the " + state + " lever on the north wall, " +
	    "the test room is completely bare.";
	break;
    case "wall":
	desc = "In the center of the north wall is " +
	    "a sturdy wooden lever. The lever is " + state + ".";
	break;
    case "lever":
	desc = "The sturdy wooden lever, about three feet long, " +
	    "is perfectly centered on the north wall. " +
	    "It is " + state + ".";
	break;
    default:
	desc = "";	/* this "cannot happen" */
	break;
    }
    return BSN(desc);
} /* look_at */


/*
 * Function name:	mess_with_lever
 * Description	:	raise or lower the lever
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
mess_with_lever(string arg)
{
    if (!strlen(arg))
    {
	return 0;
    }

    arg = LOW(arg);
    /* this accepts:
     *		lever
     *		wooden lever
     *		sturdy lever
     *		sturdy wooden lever
     * plus all of the above prefixed with "the".
     * see /d/Gondor/common/doc/parse_command/README for more info.
     */
    if (!parse_command(arg, ({}), "[the] [sturdy] [wooden] 'lever'"))
    {
	return 0;
    }

    if (QVB == "raise")
    {
	if (!Lever_is_up)
	{
	    write("You raise the lever.\n");
	    SAY(" raises the lever.");
	    tell_room(TO,
		"Somewhere in the distance, there is a loud CLANG!\n");
	    Lever_is_up = 1;
	}
	else
	{
	    write("The lever is already raised.\n");
	}
    }
    else	/* verb is "lower" */
    {
	if (Lever_is_up)
	{
	    write("You lower the lever.\n");
	    SAY(" lowers the lever.");
	    Lever_is_up = 0;
	}
	else
	{
	    write("The lever is already lowered.\n");
	}
    }
    return 1;
} /* mess_with_lever */
