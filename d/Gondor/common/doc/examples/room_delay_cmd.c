/*
 * /d/Gondor/common/doc/examples/room_delay_cmd.c
 *
 * An example of using add_delay_cmd_item() from ~gondor/std/delay_room.c
 *
 * add_delay_cmd_item() is similar to add_cmd_item(), but instead of
 * immediately writing the results of the command, it writes a beginning
 * message, paralyzes the player for some period (similiar to the way
 * "search" paralyzes), then writes a finishing message.
 *
 * the prototype is:
 * public int	add_delay_cmd_item(mixed name, mixed verb, mixed stop_msg,
 *			mixed delay, mixed begin_msg, mixed finish_msg);
 * delay may be an integer or an array of integers, the others may be
 * a string or an array of strings.
 *
 * begin_msg and finish_msg may use VBFC. if the VBFC for the begin_msg
 * returns 0, the command fails.  begin_msg is responsible for doing the
 * appropriate calls to notify_fail(), in that case.
 *
 * if the room uses VBFC and keeps some state about who is doing the command,
 * then it must mask stop_delay_cmd(mixed arg) and, if arg is not an object
 * (i.e., the player did "stop"), unset the state.
 *
 * it is safe to use this_player() in begin_msg and finish_msg VBFC.
 *
 * if begin_msg does not use VBFC, the message:
 *	QCTNAME(TP) + " begins " + stop_msg + ".\n"
 * is displayed to the room.  it follows that stop_msg should be reasonably
 * complete ... e.g., "polishing the table", rather than "polishing"
 *
 * the message:
 *	"You stop " + stop_msg + ".\n"
 * is displayed to the player if s/he does "stop".
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/delay_room";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

static int	Polished;	/* is the table polished? */
static string	Polishing;	/* name of person actively polishing */

/* prototypes */
public void	create_gondor();
public void	reset_room();
public void	leave_inv(object ob, object dest);
public string	exa_table();
public mixed	begin_polish();
public string	end_polish();
public int	stop_delay_cmd(mixed arg);


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor() 
{
    set_short("test room");
    set_long("A test room, empty except for a table and a basket.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Gondor/workroom", "out");

    /* the basket is a simple example -- the start and end mesages
     * are just strings.
     */
    add_item( ({ "junk in basket", "junk", "basket" }),
	BSN("The basket is crammed full of junk. Clearly no attempt "+
	"has been made to organize it."));
    add_delay_cmd_item( ({ "junk", "basket", }),
	"organize", "organizing the junk in the basket", 10, 
	"You begin to organize the junk in the basket.\n",
	"You give up -- it's impossible to organize this junk!\n");

    /*
     * the table is more complicated. we use VBFC for starting and ending
     * the command, so it can fail (if the table is already polished,
     * or if someone else is polishing) and so that if it succeeds,
     * the state of the table is actually changed.
     */
    add_item( ({ "reddish wood", "wood", "wooden table", "table" }),
	exa_table);
    add_delay_cmd_item( ({ "reddish wood", "wood", "wooden table", "table" }),
	"polish", "polishing the table", 20, begin_polish, end_polish);

    reset_room();
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	make the table dull again
 */
public void
reset_room()
{
    Polished = 0;
} /* reset_room */


/*
 * Function name:	leave_inv
 * Description	:	catch any polishers leaving ... they can't
 *			do it on their own, but they might be trans'd
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    if (Polishing == ob->query_name())
    {
	Polishing = "";
    }
    ::leave_inv(ob, dest);
} /* leave_inv */


/*
 * Function name:	exa_table
 * Description	:	VBFC for the table description
 * Returns	:	string -- the description
 */
public string
exa_table()
{
    if (!Polished)
    {
	return "The wooden table is dull, and in need of a polish.\n";
    }
    return "The reddish wood of the table gleams.\n";
} /* exa_table */


/*
 * Function name:	begin_polish
 * Description	:	VBFC for beginning the polish command
 * Returns	:	mixed: integer -- 0 if command fails,
 *			    or string  -- the "You begin..." message
 */
public mixed
begin_polish()
{
    if (!Polished)
    {
	if (!strlen(Polishing))
	{
	    Polishing = TP->query_name();
	    SAY(" begins polishing the table.");
	    return "You begin polishing the table.\n";
	}
	notify_fail(Polishing+" is already polishing the table.\n");
    }
    else
    {
	notify_fail("The table does not need polishing.\n");
    }
    return 0;
} /* begin_polish */


/*
 * Function name:	end_polish
 * Description	:	VBFC for finishing the polish command
 *			updates the table state.
 * Returns	:	string -- the "you finish" msg
 */
public string
end_polish()
{
   Polished = 1;
   Polishing = "";
   SAY(" finishes polishing the table. The wood glows.");
   return "You finish polishing the table. The wood glows.\n";
} /* end_polish */


/*
 * Function name:	stop_delay_cmd
 * Description	:	mask parent so that if player does "stop",
 *			we clear Polishing
 * Arguments	:	mixed arg -- if string, player did "stop"
 *				  -- if object, time ran out or
 *				      called from leave_inv().
 * Returns	:	0 -- stop is always allowed
 */
public int
stop_delay_cmd(mixed arg)
{
    object	tp;

    if (!objectp(arg))
    {
	/* called from paralyze object when player did "stop" */
	tp = ENV(previous_object());
	if (tp->query_name() == Polishing)
	{
	    Polishing = "";
	}
    }
    return ::stop_delay_cmd(arg);
} /* stop_delay_cmd */
