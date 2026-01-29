/*
 * - seating.c
 *
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#include "../zigg.h"

/***************************************************************************
 * Defines - Various defines to manage things in a more friendly manner.   *
 ***************************************************************************/

/*
 * ROOM_AS_SEATID - Added to room, contains array of seating id's.
 * ROOM_AO_SEATOB - Added to room, contains array of seating objects.
 */
#define ROOM_AS_SEATID  "_room_as_seating_ids"
#define ROOM_AO_SEATOB  "_room_ao_seating_obs"

/*
 * These are the states a seated person may be in.
 */
#define SS_NORMAL      0	/* Person is sitting normally.             */
#define SS_STRETCH     1	/* Person is stretched out.                */

/*
 * These are the lap states for seated persons.
 */
#define SS_NO_LAP      0	/* Our lap is devoid, woe!                 */
#define SS_LAP_TAKEN   1	/* Our lap is taken, yummy!                */
#define SS_IN_LAP      2	/* We are warming someone's lap, joy!      */

/*
 * Indices into the main seated array for a seated player.
 */
#define SS_STATE       0	/* Our state of sitting.                   */
#define SS_LSTATE      1	/* The status of our lap.                  */
#define SS_PLAYER      2	/* Who is in our lap, if anyone.           */

/*
 * A shadow that gets cloned to people that sit.
 */
#define SS_SHADOW    (ZIG_LIB + "seat_shadow")

/*
 * Convenience defines.
 */
#define AVAIL  (max_seat - taken)

#ifndef TP
#define TP      this_player()
#endif


/***************************************************************************
 * Variables - information, optional and required, to manage seating.      *
 ***************************************************************************/

/*
 * m_seated = ([
 *	(object)sitting : (mixed *)({
 *		(int)SS_STATE, (int)SS_LSTATE, (object)SS_PLAYER,
 *	}), ]);
 */
private static mapping m_seated = ([]);

/*
 * Internal use only variables.
 */
private static int block_props = 0,
		   cur_weight  = 0,
		   cur_volume  = 0,
		   seat_weight = 0,
		   seat_volume = 0,
		   no_deny     = 0;

private static mixed seat_no_get = 0;

/*
 * Defaults for integer options.
 * See the associated set/query functions to see what these handle.
 */
public static int max_seat    = 1,
                  lay_num     = 0,
		  taken       = 0,
                  allow_kinky = 0,
                  shift_seat  = 0,
		  visible     = 0,
		  portable    = 0;

/*
 * Defaults for string options.
 * See the associated set/query functions to see what these handle.
 */
public static string seat_id    = "_std_seating",
                    *sit_cmds   = ({ "sit", "lounge"  }),
                    *lay_cmds   = ({ "lay", "lie", "recline" }),
                    *stand_cmds = ({ "stand" }),
                    *stand_args = ({ "up"    }),
                    *seat_names = ({ "chair" });

/***************************************************************************
 * Optionals - Functions to set and query the various seating options.     *
 ***************************************************************************/

/*
 * Function name: set_max_seat
 * Description	: Determines how many people may be seated normally
 *                upon this particular seating arrangement.
 * Arguments	: int arg - The number of persons to sit normally.
 * Returns	: Void
 */
public void
set_max_seat(int arg)		{ max_seat = arg; }

/*
 * Function name: query_max_seat
 * Description	: Displays how many people may be seated normally
 *                upon this particular seating arrangement.
 * Returns	: int - # of available seats.
 */
public int
query_max_seat(void)		{ return max_seat; }

/*
 * Function name: set_lay_num
 * Description	: Determines how many seats are required/taken up for
 *                a person to stretch out on this arrangement.
 * Arguments	: int arg - # of seats.
 * Returns	: Void
 */
public void
set_lay_num(int arg)		{ lay_num = arg; }

/*
 * Function name: query_lay_num
 * Description	: Displays how many seats are required/taken up for
 *                a person to stretch out on this arrangement.
 * Returns	: int - # of seats.
 */
public int
query_lay_num(void)		{ return lay_num; }

/*
 * Function name: set_allow_kinky
 * Description	: Determines if people may sit in a normally seated
 *                persons lap or not.
 * Arguments	: int arg - 1 (yes) / 0 (no)
 * Returns	: Void
 */
public void
set_allow_kinky(int arg)	{ allow_kinky = arg; }

/*
 * Function name: query_allow_kinky
 * Description	: Displays if normally seated people may others
 *                seated upon their laps.
 * Returns	: int - 1 (yes) / 0 (no)
 */
public int
query_allow_kinky(void)		{ return allow_kinky; }

/*
 * Function name: set_shift_seat
 * Description	: Determines whether or not an in-lap person will move
 *                to an available seat or get dumped on the floor when
 *                the person they are sitting on leaves.
 * Arguments	: int arg - 1 (swap seats) / 0 (dumped on floor)
 * Returns	: Void
 */
public void
set_shift_seat(int arg)		{ shift_seat = arg; }

/*
 * Function name: query_shift_seat
 * Description	: Displays whether or no an in-lap person gets dumped
 *                to the floor when the person they are sitting on leaves.
 * Arguments	: int - 1 (swap seats) / 0 (dumped on floor)
 */
public int
query_shift_seat(void)		{ return shift_seat; }

/*
 * Function name: set_visible
 * Description	: Determines how visible this seating object is.
 * Arguments	: int arg - Default is "0", arg values mean:
 * 		   0  ==  Object never visible.
 * 		   1  ==  Dynamically visible (if nobody seated, show).
 * 		   2  ==  Object always visible.
 * Returns	: Void
 */
public void
set_visible(int arg)		{ visible = arg; }

/*
 * Function name: query_visible
 * Description	: Displays how visible this seating object is.
 * Returns	: int - Visibility status, values mean:
 * 		   0  ==  Never visible.
 * 		   1  ==  Visible if unused.
 * 		   2  ==  Always visible.
 */
public int
query_visible(void)		{ return visible; }

/*
 * Function name: set_portable
 * Description	: Determines if this seating object is portable.
 * Arguments	: int arg - 0 = no / 1 = yes.
 * Returns	: Void
 */
public void
set_portable(int arg)		{ portable = arg; }

/*
 * Function name: query_portable
 * Description	: Displays how portable this seating object is.
 * Returns	: int - 0 = no / 1 = yes.
 */
public int
query_portable(void)		{ return portable; }

/*
 * Function name: set_seat_id
 * Description	: Determines the unique identifier of this seating arrangement.
 *                Only one item per seat_id is allowed in a room at any given
 *                time, so different items need different id's to co-exist.
 * Arguments	: string arg - the unique id for this object.
 * Returns	: Void
 */
public void
set_seat_id(string arg)		{ seat_id = arg; }

/*
 * Function name: query_seat_id
 * Description	: Displays the unique id for this seating arrangement.
 * Returns	: string - the unique id.
 */
public string
query_seat_id(void)		{ return seat_id; }

/*
 * Function name: set_sit_cmds
 * Description	: Sets the commands available to persons to sit 
 * 		  on this object.
 * Arguments	: string *arg - array of valid commands.
 * Returns	: Void
 */
public void
set_sit_cmds(string *arg)	{ sit_cmds = arg; }

/*
 * Function name: query_sit_cmds
 * Description	: Displays the commands available to persons to sit 
 * 		  on this object.
 * Arguments	: string * - array of valid commands.
 */
public string *
query_sit_cmds(void)		{ return secure_var(sit_cmds); }

/*
 * Function name: set_stand_cmds
 * Description	: Sets the commands available to persons to stand up
 *                from this object.
 * Arguments	: string *arg - array of valid commands.
 * Returns	: Void
 */
public void
set_stand_cmds(string *arg)	{ stand_cmds = arg; }

/*
 * Function name: query_stand_cmds
 * Description	: Displays the commands available to persons to stand up
 *                from this object.
 * Returns	: string * - array of valid commands.
 */
public string *
query_stand_cmds(void)		{ return secure_var(stand_cmds); }

/*
 * Function name: set_stand_args
 * Description	: Sets the arguments available to persons to stand up
 *                from this object.
 * Arguments	: string *arg - array of valid arguments.
 * Returns	: Void
 */
public void
set_stand_args(string *arg)	{ stand_args = arg; }

/*
 * Function name: query_stand_args
 * Description	: Displays the arguments available to persons to stand up
 *                from this object.
 * Returns	: string * - array of valid commands.
 */
public string *
query_stand_args(void)		{ return secure_var(stand_args); }

/*
 * Function name: set_lay_cmds
 * Description	: Sets the commands available to persons to 
 * 		  lay upon this object.
 * Arguments	: string *arg - array of valid commands.
 * Returns	: Void
 */
public void
set_lay_cmds(string *arg)	{ lay_cmds = arg; }

/*
 * Function name: query_lay_cmds
 * Description	: Displays the commands available to persons to lay
 *                upon this object.
 * Returns	: string * - array of valid commands.
 */
public string *
query_lay_cmds(void)		{ return secure_var(lay_cmds); }

/*
 * Function name: set_seat_names
 * Description	: Sets the names this object might be accessed by.
 * Arguments	: string *arg - array of valid names.
 * Returns	: Void
 */
public void
set_seat_names(string *arg)	{ seat_names = arg; }

/*
 * Function name: query_seat_names
 * Description	: Displays the names this object might be accessed by.
 * Returns	: string * - array of valid names.
 */
public string *
query_seat_names(void)		{ return secure_var(seat_names); }

/*
 * Function name: query_seated
 * Description	: Displays information about seated person(s).
 * Arguments	: (optional) object who - Specific information on <who>.
 * Returns	: mapping  - information on all seated persons.
 *                string * - information on seated person <who>.
 */
public varargs mixed
query_seated(object who)
{
    if (objectp(who))
	return secure_var(m_seated[who]);
    else
	return secure_var(m_seated);
}

/*
 * Function name: query_sitting
 * Description	: Displays information about seated person(s).
 * Arguments	: (optional) object who - Specific information on <who>.
 * Returns	: object * - All people seated.
 * 		  object   - Whose lap are we under / on.
 */
public varargs mixed
query_sitting(object who)
{
    m_delkey(m_seated, 0);
    if (objectp(who))
    {
	if (m_seated[who])
	    return m_seated[who][SS_PLAYER];
	else
	    return 0;
    }

    if (!m_sizeof(m_seated))
	return ({});
    else
	return m_indexes(m_seated);
}

/*
 * Function name: query_taken
 * Description	: Displays number of seats presently taken.
 * Returns	: int - # of seats taken.
 */
public int
query_taken(void)		{ return taken; }

/***************************************************************************
 * Hooks - Maskable functions to alter the various informational messages. *
 ***************************************************************************/

/*
 * Function name: ss_seat_syntax
 * Description	: Handles notify_fail() message when bad command is given.
 * Returns	: Void
 */
public void
ss_seat_syntax(void)
{
    notify_fail(capitalize(query_verb()) + " [down] [on] / [in] "+
        (allow_kinky ? "who/what" : "what") + "?\n");
}

/*
 * Function name: ss_no_room
 * Description	: Handles failure message when there is no room to sit.
 * Arguments	: int stretch - If we were trying to sit or stretch.
 * Returns	: Void
 */
public void
ss_no_room(int stretch)
{
    if (stretch)
	write("There is no room left to lay down.\n");
    else
	write("There is no room left for you.\n");
}

/*
 * Function name: ss_no_allow_move
 * Description	: Handles messages when we don't really move.
 * Arguments	: int state - Our seated state.
 * Returns	: Void
 */
public void
ss_no_allow_move(int state)
{
    switch(state)
    {
    default:
	/* Fallthru */
    case SS_NORMAL:
	write("You move around on the "+ short() +", "+
	    "trying to get more comfortable.\n");
	say(QCTNAME(TP) +" moves around on the "+ short() +", "+
	    "trying to get more comfortable.\n");
	break;

    case SS_STRETCH:
	write("You stretch out some more on the "+ short() +".\n");
	say(QCTNAME(TP) +" stretches out some more on the "+
	    short() + ".\n", TP);
	break;
    }
}

/*
 * Function name: ss_no_allow_shift_lap
 * Description	: Handles messages when we try to shift directly
 * 		  from one lap to another.
 * Arguments	: object from - Lap we are in.
 * 		  object   to - Lap we tried to go to.
 * Returns	: Void
 */
public void
ss_no_allow_shift_lap(object from, object to)
{
    write("Shifting laps isn't as easy as it looks, "+
	"try standing up first.\n");
}

/*
 * Function name: ss_no_allow_move_lap
 * Description	: Handles messages when we don't really move,
 *                while someone is presently on our lap.
 * Arguments	: object lap - Person in our lap.
 * 		   int state - Our seated state.
 * Returns	: Void
 */
public void
ss_no_allow_move_lap(object lap, int state)
{
    switch(state)
    {
    default:
	/* Fallthru */
    case SS_NORMAL:
	write("You squirm around a bit beneath " +
	    lap->query_the_name(TP) +
	    " trying to get comfy.\n");
	lap->catch_tell(TP->query_The_name(lap) +
	    " squirms beneath you some.\n");
	break;

    case SS_STRETCH:
	write("You stetch out a bit further beneath " +
	    lap->query_the_name(TP) +".\n");
	lap->catch_tell(TP->query_The_name(lap) +
	    " stretches out a bit more beneath you.\n");
	break;
    }
}

/*
 * Function name: ss_no_allow_move_in_lap
 * Description	: Handles messages when we don't really move,
 *                while someone is presently on our lap.
 * Arguments	: object lap - Person in our lap.
 * 		   int state - Our seated state.
 * Returns	: Void
 */
public void
ss_no_allow_move_in_lap(object lap, int state)
{
    write("You squirm around a bit atop " +
	lap->query_the_name(TP) +
	" as you look for an empty spot, but find none.\n");
    lap->catch_tell(TP->query_The_name(lap) +
	" squirms atop you some.\n");
}

/*
 * Function name: ss_allow_move_leave_lap
 * Description	: Handles messages when we climb out of someone's lap.
 * Arguments	: object lap - The lap we are leaving.
 * 		   int state - Our seated state.
 * Returns	: Void
 */
public void
ss_allow_move_leave_lap(object lap, int state)
{
    string verb = query_verb();

    switch(state)
    {
    default:
	/* Fallthru */
    case SS_NORMAL:
	write("You climb out of "+
	    lap->query_the_possessive_name(TP) +
	    " lap to "+ verb +" beside "+ lap->query_objective() +".\n");
	lap->catch_tell(TP->query_The_name(lap) +
	    " climbs out of your lap to "+ verb +" beside you.\n");
	say(QCTNAME(TP) +" climbs out of "+ QTPNAME(lap) +
	    " lap to "+ verb +" beside "+ lap->query_objective() +".\n",
	    ({ TP, lap }));
	break;

    case SS_STRETCH:
	write("You slip from atop "+ lap->query_the_name(TP) +
	    " and "+ verb +" beside "+ lap->query_objective() +".\n");
	lap->catch_tell(TP->query_The_name(lap) +
	    " slips from atop your body to "+ verb +" beside you.\n");
	say(QCTNAME(TP) +" slips from atop "+ QTPNAME(lap) +
	    " body to "+ verb +" beside "+ lap->query_objective() +".\n",
	    ({ TP, lap }));
	break;
    }
}

/*
 * Function name: ss_allow_move_stretch
 * Description	: Handles messages when go from sitting to stretched posture.
 * Returns	: Void
 */
public void
ss_allow_move_stretch(void)
{
    write("You lay back and stretch out atop the "+
	short() +".\n");
    say(QCTNAME(TP) +" lays back and stretches out "+
	"atop the "+ short() +"\n", ({ TP }));
}

/*
 * Function name: ss_allow_move_stretch_lap
 * Description	: Handles messages when go from sitting to stretched posture
 *                with someone in our lap.
 * Arguments	: object lap - Person in our lap.
 * Returns	: Void
 */
public void
ss_allow_move_stretch_lap(object lap)
{
    write("You lay back, pulling "+ lap->query_the_name(TP) +
	" down with you as stretch out atop the "+ short() +".\n");
    lap->catch_tell(TP->query_The_name(lap) +" pulls you down "+
	"with "+ TP->query_objective() +" as "+
	TP->query_pronoun() +" stretches out on the "+
	short() +".\n");
    say(QCTNAME(TP) +" lays back, pulling "+ QTNAME(lap) +
	" with "+ TP->query_objective() +" as "+
	TP->query_pronoun() +" stretches out on the "+
	short() +".\n", ({ TP, lap }));
}

/*
 * Function name: ss_allow_move_stretch_in_lap
 * Description	: Handles messages when go from sitting to stretched posture
 *                while in someone's lap.
 * Arguments	: object lap - The lap we are in.
 * Returns	: Void
 */
public void
ss_allow_move_stretch_in_lap(object lap)
{
    write("You push "+ lap->query_the_name(TP) +
	" back and stretch out atop "+ lap->query_objective() +
	" on the "+ short() +".\n");
    lap->catch_tell(TP->query_The_name(lap) +
	" pushes you down against the "+ short() +
	" and stretches out atop you.\n");
    say(QCTNAME(TP) +" pushes "+ QTNAME(lap) +
	" down and stretches out atop "+ lap->query_objective() +
	" on the "+ short() +".\n", ({ TP, lap }));
}

/*
 * Function name: ss_allow_move_sit
 * Description	: Handles messages when go from stretched to sitting posture.
 * Returns	: Void
 */
public void
ss_allow_move_sit(void)
{
    write("You sit up on the "+ short() +".\n");
    say(QCTNAME(TP) +" sits up on the "+ short() +".\n",
	({ TP }));
}

/*
 * Function name: ss_allow_move_sit_from_lap
 * Description	: Handles messages when go from stretched to sitting posture
 *                while in someone's lap.
 * Arguments	: object lap - The lap we are in.
 * Returns	: Void
 */
public void
ss_allow_move_sit_from_lap(object lap)
{
    string verb1 = query_verb(),
	   verb2 = LANG_PWORD(verb1);

    write("You crawl off of "+ lap->query_the_name(TP) +
	" and "+ verb1 +" on the "+ short() +".\n");
    lap->catch_tell(TP->query_The_name(lap) +
	" crawls off of you and "+ verb2 +" on the "+ short() +".\n");
    say(QCTNAME(TP) +" crawls off of "+ QTNAME(lap) +" and "+
	verb2 +" on the "+ short() +".\n", ({ TP, lap }));
}

/*
 * Function name: ss_seated
 * Description	: Handles messages for someone sitting.
 * Arguments	: int state - Our seated state.
 * Returns	: Void
 */
public void
ss_seated(int state)
{
    string verb = query_verb();

    switch(state)
    {
    case SS_NORMAL:
	write("You "+ verb +" down on the "+ short() +".\n");
	say(QCTNAME(TP) +" "+ LANG_PWORD(verb) +" down on the "+
	    short() +".\n");
	break;

    case SS_STRETCH:
	write("You "+ verb +" down on the "+ short() +
	    " and stretch out.\n");
	say(QCTNAME(TP) +" "+ LANG_PWORD(verb) +" down on the "+
	    short() +" and stretches out.\n");
	break;
    }
}

/*
 * Function name: ss_seated_lap
 * Description	: Handles messages for someone sitting atop another.
 * Arguments	: object lap - The lap we are sitting on.
 * 		   int state - Our seated state.
 * 		   int force - Force 'lap' into a stretch.
 * Returns	: Void
 */
public void
ss_seated_lap(object lap, int state, int force)
{
    if (force)
    {
	write("You push "+ lap->query_the_name(TP) +" back and "+
	    "stretch out atop "+ lap->query_objective() +".\n");
	lap->catch_tell(TP->query_The_name(lap) +
	    " pushes you back and stretches out atop you.\n");
	say(QCTNAME(TP) + " pushes "+ QTNAME(lap) +" back and "+
	    "stretches out atop "+ lap->query_objective() +".\n",
	    ({ TP, lap }));
    }
    else switch(state)
    {
    case SS_NORMAL:
	write("You climb into "+
	    lap->query_the_possessive_name(TP) +" lap.\n");
	lap->catch_tell(TP->query_The_name(lap) +
	    " climbs into your lap.\n");
	say(QCTNAME(TP) + " climbs into " + QTPNAME(lap) +
	    " lap.\n", ({ TP, lap }));
	break;

    case SS_STRETCH:
	write("You stretch out atop "+
	    lap->query_the_name() +".\n");
	lap->catch_tell(TP->query_The_name(lap) +
	    " stretches out atop you.\n");
	say(QCTNAME(TP) + " stretches out atop "+
	    QTNAME(lap) +".\n", ({ TP, lap }));
	break;
    }
}

/*
 * Function name: ss_already_stand
 * Description	: Handles notify_fail() message for a person
 *                trying to sit who isn't sitting.
 * Returns	: Void
 */
public void
ss_already_stand(void)
{
    notify_fail("But you are not seated!\n");
}

/*
 * Function name: ss_stand
 * Description	: Handles messages for someone standing up.
 * Returns	: Void
 */
public void
ss_stand(void)
{
    write("You arise from the "+ short() +".\n");
    say(QCTNAME(TP) + " arises from the "+ short() +".\n");
}

/*
 * Function name: ss_stand_lap
 * Description	: Handles messages for someone standing up
 *                from anothers lap.
 * Arguments	: object lap - Lap we are leaving.
 * Returns	: Void
 */
public void
ss_stand_lap(object lap)
{
    write("You climb off of "+
	lap->query_the_possessive_name(TP) + " lap.\n");
    lap->catch_tell(TP->query_The_name(lap) +
	" climbs off of your lap.\n");
    say(QCTNAME(TP) + " climbs out of " + QTPNAME(lap) +" lap.\n",
	({ TP, lap}));
}

/*
 * Function name: ss_shift_seat
 * Description	: Handles messages for someone transferring from anothers
 *                lap and onto a regular seat.
 * Arguments	: object who - Person getting shifted.
 * Returns	: Void
 */
public void
ss_shift_seat(object who)
{
    who->catch_tell("You move onto the "+ short() +".\n");
    write(who->query_The_name(TP) +" moves onto the "+ short() +".\n");
    tell_room(environment(), QCTNAME(who) +" moves onto the "+
        short() +".\n", ({ who, TP }));
}

/*
 * Function name: ss_dumped
 * Description	: Handles messages for someone getting dumped out of
 *                another lap and there is no room for them elsewhere.
 * Arguments	: object who - Person getting dumped.
 * Returns	: Void
 */
public void
ss_dumped(object who)
{
    who->catch_tell("You are dumped unceremoniously "+
        "onto the "+ (environment(who)->query_prop(ROOM_I_INSIDE) ?
	   "floor" : "ground") + ".\n");

    tell_room(environment(who),
	QCTNAME(who) + " is dumped unceremoniously onto the" +
	(environment(who)->query_prop(ROOM_I_INSIDE) ? 
	   "floor" : "ground") + ".\n", who);
}

/***************************************************************************
 * Description - Functions to handle seated descriptions.                  *
 ***************************************************************************/

/*
 * Function name: sit_text
 * Description	: Text to describe sitting posture in seat_desc().
 * Returns	: string
 */
public string
sit_text(void)		{ return "sitting on"; }

/*
 * Function name: lay_text
 * Description	: Text to describe stretched posture in seat_desc().
 * Returns	: string
 */
public string
lay_text(void)		{ return "stretched out"; }

public string
lay_text_on(void)	{ return "stretched out on"; }

/*
 * Function name: seat_desc
 * Description	: Provides descriptive information about this particular
 *                seating arrangement, including optionals.
 * Returns	: string - descriptive text.
 */
public nomask string
seat_desc(void)
{
    int sz;
    string str = "";
    mixed *who = ({ ({}), ({}), ({}), ({}) });

    if (!m_sizeof(m_seated))
    {
	taken = 0;
	return str;
    }

    /* Gather names and states here. */
    foreach(object ob, mixed *tmp : m_seated)
    {
	if (tmp[SS_LSTATE] == SS_IN_LAP)
	{
	    object lap = tmp[SS_PLAYER];

	    if (tmp[SS_STATE] == SS_NORMAL)
	    {
		who[2] += ({
		    (ob == TP ? "you are" : ob->query_the_name(TP) +" is") +
		    " in "+ (lap == TP ? (sizeof(who[2]) ? "yours" :
			"your") : lap->query_the_possessive_name(TP))
		});
	    }
	    else
	    {
		who[3] += ({
		    (ob == TP ? "you are" : ob->query_the_name(TP) +" is") +
		    " "+ lay_text_on() +" "+ (lap == TP ? "you" :
			lap->query_the_name(TP))
		});
	    }
	}
	else if (tmp[SS_STATE] == SS_NORMAL)
	{
	    who[0] += ({
		(ob == TP ? "you" : ob->query_the_name(TP))
	    });
	}
	else
	{
	    who[1] += ({
		(ob == TP ? "you" : ob->query_the_name(TP))
	    });
	}
    }

    /* Normal */
    if (sz = sizeof(who[0]))
    {
	str += capitalize(COMPOSITE_WORDS(who[0]) +" "+ (sz == 1 ?
	    (who[0][0] == "you" ? "are": "is") : "are") +
	    " "+ sit_text() +" the "+ short() +".\n");
    }

    /* Stretched */
    if (sz = sizeof(who[1]))
    {
	str += capitalize(COMPOSITE_WORDS(who[1]) +" "+ (sz == 1 ?
	    (who[1][0] == "you" ? "are": "is") : "are"));

	if (sz = sizeof(who[0]))
	{
	    str += " "+ lay_text() +" next to "+
		(IN_ARRAY("you", who[0]) ? "you" : "them") +".\n";
	}
	else
	{
	    str += " "+ lay_text_on() +" the "+ short() +".\n";
	}
    }

    /* Lapped */
    if (sizeof(who[2]))
    {
	who[2][0] += " lap";

	if (sizeof(who[3]))
	    str += capitalize(COMPOSITE_WORDS(who[2] + who[3]) + ".\n");
	else
	    str += capitalize(COMPOSITE_WORDS(who[2]) + ".\n");
    }
    else if (sizeof(who[3]))
	str += capitalize(COMPOSITE_WORDS(who[3]) + ".\n");

    /* Put it all together. */
    return str;
}

/***************************************************************************
 * Props - Functions to handle property management.                        *
 ***************************************************************************/

/* Block the changing of these properties. */
public nomask int add_prop_obj_i_weight(void)	 { return block_props; }
public nomask int add_prop_obj_i_volume(void)	 { return block_props; }
public nomask int add_prop_obj_m_no_get(void)	 { return block_props; }
public nomask int remove_prop_obj_i_weight(void) { return 1; }
public nomask int remove_prop_obj_i_volume(void) { return 1; }
public nomask int remove_prop_obj_m_no_get(void) { return 1; }

/*
 * Function name: update_props
 * Description	: Updates the weight and volume properties as
 * 		  people sit and stand on this object.
 * Arguments	: int weight - The added (or subtracted) weight.
 * 		  int volume - The added (or subtracted) volume.
 * Returns	: Void
 */
private void
update_props(int weight, int volume)
{
    if (weight)  cur_weight += weight;
    if (volume)  cur_volume += volume;

    if (cur_weight < 0)  cur_weight = 0;
    if (cur_volume < 0)  cur_volume = 0;
}

/*
 * Function name: prop_weight
 * Description	: Returns total weight of this object plus those seated.
 * Returns	: int - total weight
 */
private int
prop_weight(void)	{ return seat_weight + cur_weight; }

/*
 * Function name: prop_volume
 * Description	: Returns total volume of this object plus those seated.
 * Returns	: int - total volume
 */
private int
prop_volume(void)	{ return seat_volume + cur_volume; }

/*
 * Function name: prop_no_get
 * Description	: Determines if the object is takeable or not.
 * Returns	: mixed - string failure message.
 * 			- int 0 = no / 1 = yes.
 */
private mixed
prop_no_get(void)
{
    if (!portable)
    {
	/* Not portable, fail. */
	if (strlen(seat_no_get))
	    return seat_no_get;

	return 1;
    }

    /* Not occupied. */
    if (!taken)
	return 0;

    /* Occupied. */
    return "   The "+ short() +
	   " can not be taken while it is occupied.\n";
}

/***************************************************************************
 * Creation - Functions to handle object creation.                         *
 ***************************************************************************/

/*
 * Function name: create_seating
 * Description	: This is the function that should be masked by
 *                inheriting files and all setup-code placed within,
 *                including the enabling of options, which are all
 *                disabled by default.
 * Returns	: Void
 */
public void
create_seating(void)
{
    /*
     * Set some defaults for playing with.
     * These will be lost when masked, which is intended.
     */
    set_name("chair");
    set_short("worn-out chair");
    set_adj(({"worn", "worn-out"}));
    set_long("A rather worn-out and beat up looking chair.\n");

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 6500);

    set_visible(1);
    set_portable(1);
    set_allow_kinky(1);
}

/*
 * Masked and set nomask.
 * Inheriting objects should mask create_seating() instead.
 * See: sman /std/object create_object
 */
public nomask void
create_object(void)
{
    setuid();
    seteuid(getuid());

    /* Call maskable creation routine. */
    create_seating();

    /* Capture existing properties. */
    seat_weight = query_prop(OBJ_I_WEIGHT);
    seat_volume = query_prop(OBJ_I_VOLUME);
    seat_no_get = query_prop(OBJ_M_NO_GET);

    /* Change and lock properties to dynamic values. */
    add_prop(OBJ_I_WEIGHT, prop_weight);
    add_prop(OBJ_I_VOLUME, prop_volume);
    add_prop(OBJ_I_NO_GET, prop_no_get);
    block_props = 1;
}

/***************************************************************************
 * Tracking - Functions to handle tracking information of the object       *
 ***************************************************************************/

/*
 * Function name: add_seating_info
 * Description	: Adds information about this seating arrangement to the
 *                room for tracking purposes. Also takes care of adding
 *                optional information to the room as well.
 * Arguments	: object room - The room to update.
 * Returns	: Void
 */
static void
add_seating_info(object room, object from)
{
    /* Get current information from room. */
    object *seats = (object *)room->query_prop(ROOM_AO_SEATOB);
    string *seat_ids = (string *)room->query_prop(ROOM_AS_SEATID);;

    /* No pre-existsing information, start new. */
    if (!pointerp(seat_ids))
    {
	seats = ({ });
	seat_ids = ({ });
    }

    /* Something with our seat_id is already present. */
    if (IN_ARRAY(seat_id, seat_ids))
    {
	write("One "+ short() +" in a room is enough.\n");
	if (query_interactive(from))
	    move(from);
	else
	    remove_object();

	return;
    }

    /* Update tracking information to include us. */
    seat_ids += ({ seat_id });
    seats += ({ this_object() });

    /* Add updated information to the room. */
    room->add_prop(ROOM_AO_SEATOB, seats);
    room->add_prop(ROOM_AS_SEATID, seat_ids);

    room->add_subloc(seat_id, this_object(), "seating");
}

/*
 * Function name: remove_seating_info
 * Description	: Removes information about this seating arrangement to the
 *                room for tracking purposes. Also takes care of removing
 *                optional information added to the room as well.
 * Arguments	: object room - The room to update.
 * Returns	: Void
 */
static void
remove_seating_info(object room)
{
    /* Get current information from room. */
    object *seats = (object *)room->query_prop(ROOM_AO_SEATOB);
    string *seat_ids = (string *)room->query_prop(ROOM_AS_SEATID);;

    /* Odd, there is no seating information. */
    if (!sizeof(seat_ids))
	return;

    /* Odd, we are not present in the seating information. */
    if (!IN_ARRAY(seat_id, seat_ids))
	return;

    if (!sizeof(seats))
    {
	/* We were the only one, remove props entirely. */
	room->remove_prop(ROOM_AO_SEATOB);
	room->remove_prop(ROOM_AS_SEATID);
    }
    else
    {
	/* Remove us from the seating information. */
	seats -= ({ this_object() });
	seat_ids -= ({ seat_id });

	/* Re-add information for other seating arrangements. */
	room->add_prop(ROOM_AO_SEATOB, seats);
	room->add_prop(ROOM_AS_SEATID, seat_ids);
    }

    room->remove_subloc(seat_id);
}

/*
 * Masked to handle adding information to rooms.
 * See: sman /std/object enter_env
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    add_seating_info(dest, old);
}

/*
 * Masked to handle removing information from rooms.
 * See: sman /std/object leave_env
 */
public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    remove_seating_info(old);
}

/***************************************************************************
 * Command - Functions to handle commands made available by this object.   *
 ***************************************************************************/

/*
 * Function name: add_seat_shadow
 * Description	: Adds a shadow to a seated person for extra tracking.
 * Arguments	: object who - The person to shadow.
 * Returns	: Void
 */
static void
add_seat_shadow(object who)
{
    object ob = clone_object(SS_SHADOW);
    ob->set_seating_ob(this_object());
    ob->shadow_me(who);
}

/*
 * Function name: remove_seat_shadow
 * Description	: Removes the seating tracking shadow from a person.
 * Arguments	: object who - The person to remove the shadow from.
 * Returns	: Void
 */
static void
rem_seat_shadow(object who)
{
    who->remove_seating_shadow();
}

/*
 * Function name: deny_seat
 * Description	: Checked just before allowing someone to sit on this
 * 		  object to allow one last chance to deny it based
 * 		  on any arbitrary values.
 * Arguments	: object lap - lap we (might be) sitting on.
 * 		   int state - whether they are trying to sit or stretch.
 * Returns	: int - 0 accept / 1 - deny
 * Notes:
 * 	You must print your own denial message, as there is no
 * 	default when using this method to deny sitting access.
 */
public int
deny_seat(object lap, int state)	{ return 0; }

/*
 * Function name: deny_change
 * Description	: Checked just before allowing someone to change
 * 		  seated position to allow one last chance to deny
 * 		  it based on any arbitrary values.
 * Arguments	: object lap - lap we (might be) moving to.
 * 		   int state - New state we want to move into.
 * Returns	: int - 0 accept / 1 - deny
 * Notes:
 * 	You must print your own denial message, as there is no
 * 	default when using this method to deny change access.
 */
public int
deny_change(object lap, int state)	{ return 0; }

/*
 * Function name: deny_stand
 * Description	: Checked just before allowing someone to stand so
 * 		  as to allow one last chance to deny it based on
 * 		  any arbitrary values.
 * Returns	: int - 0 accept / 1 - deny
 * Notes:
 * 	You must print your own denial message, as there is no
 * 	default when using this method to deny change access.
 *
 * 	Do NOT try and figure in destruct, quit or linkdeath events
 * 	as those have already been taken into account and will not
 * 	be blocked by this function.
 */
public int
deny_stand(void)			{ return 0; }

/*
 * Function name: do_seat
 * Description	: This handles the sitting/stretching commands.
 * Arguments	: string str - Player text given after command verb.
 * Returns	: int - 1 (success) / 0 (failure)
 */
public nomask int
do_seat(string str)
{
    mixed *tmp;
    object *obs, ob;
    int state, stretch;

    if (!strlen(str))
	return notify_fail(capitalize(query_verb()) + " where?\n");

    /* If player is already seated, they'll have a shadow already. */
    if (objectp(ob = TP->query_seating_ob()))
    {
	/* Player seated elsewhere, fail silently to let it take over. */
	if (ob != this_object())
	    return 0;
	else
	    state = 1;
    }

    /* Do we allow player on player action? */
    if (allow_kinky)
	obs = m_indexes(m_seated) - ({ TP }) + ({ this_object() });
    else
	obs = ({ this_object() });

    /* See if any of it matches what we know about, otherwise bail. */
    if (!parse_command(str, obs, "[down] [on] / [in] [the] %o", ob))
    {
	ss_seat_syntax();
	return 0;
    }

    /* Test here if we are trying to stretch. */
    if (lay_num)
	stretch = IN_ARRAY(query_verb(), lay_cmds);
    
    /* Handle unseated->seated first. */
    if (!state)
    {
	/* Target is already seated. */
	if (m_seated[ob])
	{
	    /* See if their lap is taken or if they are in someone elses. */
	    if (objectp(m_seated[ob][SS_PLAYER]))
	    {
		ss_no_room(stretch);
		return 1;
	    }

	    /* Initial state of seated person. */
	    state = m_seated[ob][SS_STATE];

	    /* We want to stretch, so accomodate if room. */
	    if (stretch &&
		(state != SS_STRETCH) &&
		(AVAIL >= (lay_num - 1)))
	    {
		state = SS_STRETCH;
		taken += (lay_num - 1);
	    }
	    else
	    {
		stretch = 0;
	    }

	    /* Last chance to deny. */
	    if (deny_seat(ob, state))
		return 2;

	    /* The lap is available, lets cuddle! */
	    m_seated[ob] = ({ state, SS_LAP_TAKEN, TP });
	    m_seated[TP] = ({ state, SS_IN_LAP, ob });
	    ss_seated_lap(ob, state, stretch);
	    /* Update and return below. */
	}
	else  /* We are the target. */
	{
	    /* See if there is room. */
	    if (!AVAIL || (stretch && (AVAIL < lay_num)))
	    {
		ss_no_room(stretch);
		return 1;
	    }

	    /* What state do we wish? */
	    state = (stretch ? SS_STRETCH : SS_NORMAL);

	    /* Last chance to deny. */
	    if (deny_seat(0, state))
		return 2;

	    /* Found a free cushion, sit! */
	    taken += (stretch ? lay_num : 1);
	    m_seated[TP] = ({ state, SS_NO_LAP, 0 });
	    ss_seated(state);
	    /* Update and return below. */
	}

	/* Since we aren't yet sitting, add the shadow and hide us. */
	add_seat_shadow(TP);
	TP->set_no_show_composite(1);

	update_props(TP->query_prop(OBJ_I_WEIGHT),
		     TP->query_prop(OBJ_I_VOLUME));

	return 1;
    }

    tmp   = m_seated[TP];
    state = (stretch ? SS_STRETCH : SS_NORMAL);

    /* Target is a seated player. */
    if (m_seated[ob])
    {
	switch(tmp[SS_LSTATE])
	{
	/* We are underneath someone. */
	case SS_LAP_TAKEN:
	    /* See if we can stretch us both out. */
	    if ((ob == tmp[SS_PLAYER]) && stretch &&
		(state != tmp[SS_STATE]) && (AVAIL >= (lay_num - 1)))
	    {
		if (deny_change(0, state))
		    return 2;

		taken += (lay_num - 1);
		m_seated[ob][SS_STATE] = state;
		m_seated[TP][SS_STATE] = state;
		ss_allow_move_stretch_lap(ob);
		break;
	    }

	    /* Can't move with someone sitting atop you. */
	    ss_no_allow_move_lap(tmp[SS_PLAYER], tmp[SS_STATE]);
	    break;

	/* We are already sitting on the person. */
	case SS_IN_LAP:
	    /* Already in their lap. */
	    if (ob == tmp[SS_PLAYER])
	    {
		/* See if we can stretch us both out. */
		if (stretch &&
		    (state != tmp[SS_STATE]) &&
		    (AVAIL >= (lay_num - 1)))
		{
		    if (deny_change(0, state))
			return 2;

		    taken += (lay_num - 1);
		    m_seated[ob][SS_STATE] = state;
		    m_seated[TP][SS_STATE] = state;
		    ss_allow_move_stretch_in_lap(ob);
		    break;
		}

		/* Otherwise, squirm around. */
		ss_no_allow_move_in_lap(tmp[SS_PLAYER], tmp[SS_STATE]);
		break;
	    }

	    /* We are trying to switch laps? */
	    ss_no_allow_shift_lap(tmp[SS_PLAYER], ob);
	    break;

	/* We are sitting alone. */
	case SS_NO_LAP:
	    /* Targets lap is occupied. */
	    if (objectp(m_seated[ob][SS_PLAYER]))
	    {
		ss_no_room(0);
		break;
	    }

	    /* Initial state of seated person. */
	    state = m_seated[ob][SS_STATE];

	    /* Target is alread stretched, so we can shortcut. */
	    if (state == SS_STRETCH)
	    {
		if (deny_change(ob, state))
		    return 2;

		taken -= (tmp[SS_STATE] == state ? lay_num : 1);
		m_seated[ob] = ({ state, SS_LAP_TAKEN, TP });
		m_seated[TP] = ({ state, SS_IN_LAP, ob });
		ss_seated_lap(ob, state, 0);
		break;
	    }

	    /* We want to stretch, so accomodate if room. */
	    if (stretch)
	    {
		if (deny_change(ob, SS_STRETCH))
		    return 2;

		if (tmp[SS_STATE] == SS_STRETCH)
		    stretch += lay_num;
		else
		    stretch += 1;

		if (AVAIL >= (lay_num - stretch))
		{
		    state = SS_STRETCH;
		    taken += (lay_num - stretch);
		}
		else
		{
		    stretch = 0;
		}
		/* Update and return below. */
	    }
	    else
	    {
		if (deny_change(ob, SS_NORMAL))
		    return 2;

		taken -= 1;
	    }

	    /* The lap is available, lets cuddle! */
	    m_seated[ob] = ({ state, SS_LAP_TAKEN, TP });
	    m_seated[TP] = ({ state, SS_IN_LAP, ob });
	    ss_seated_lap(ob, state, stretch);
	    break;
	}

	return 1;
    }

    /* Target is this object */
    switch(m_seated[TP][SS_LSTATE])
    {
    case SS_LAP_TAKEN:
	/* See if we can stretch us both out. */
	if (stretch && (state != tmp[SS_STATE]) &&
	    objectp(ob = tmp[SS_PLAYER]) &&
	    (AVAIL >= (lay_num - 1)))
	{
	    if (deny_change(0, state))
		return 2;

	    taken += (lay_num - 1);
	    m_seated[ob][SS_STATE] = state;
	    m_seated[TP][SS_STATE] = state;
	    ss_allow_move_stretch_lap(ob);
	    break;
	}

	/* Can't move with someone sitting atop you. */
	ss_no_allow_move_lap(tmp[SS_PLAYER], tmp[SS_STATE]);
	break;

    case SS_IN_LAP:
	ob = tmp[SS_PLAYER];
	/* No room to leave the lap. */
	if (!AVAIL)
	{
	    ss_no_allow_move_in_lap(ob, tmp[SS_STATE]);
	    break;
	}

	if (stretch && (AVAIL >= lay_num))
	{
	    /* Leave the lap and stretch out. */
	    state = SS_STRETCH;

	    if (deny_change(0, state))
		return 2;

	    taken += lay_num;
	}
	else
	{
	    /* Leave the lap and sit normally. */
	    state = SS_NORMAL;

	    if (deny_change(0, state))
		return 2;

	    taken += 1;
	}

	/* Update status. */
	m_seated[ob] = ({ tmp[SS_STATE], SS_NO_LAP, 0 });
	m_seated[TP] = ({ state, SS_NO_LAP, 0 });
	ss_allow_move_leave_lap(ob, state);
	break;

    case SS_NO_LAP:
	/* We aren't changing state. */
	if (state == tmp[SS_STATE])
	{
	    ss_no_allow_move(state);
	    break;
	}

	/* Changing state, checking against new. */
	switch(state)
	{
	case SS_NORMAL:
	    if (deny_change(0, state))
		return 2;

	    taken -= (lay_num - 1);
	    m_seated[TP][SS_STATE] = state;
	    ss_allow_move_sit();
	    break;
	case SS_STRETCH:
	    /* Want to stretch out. */
	    if (AVAIL >= (lay_num - 1))
	    {
		if (deny_change(0, state))
		    return 2;

		taken += (lay_num - 1);
		m_seated[TP][SS_STATE] = state;
		ss_allow_move_stretch();
		break;
	    }

	    /* Just squirm. */
	    ss_no_allow_move(tmp[SS_STATE]);
	    break;
	}
	break;
    }

    return 1;
}

/*
 * Function name: do_stand
 * Description	: This handles the standing commands.
 * Arguments	: string str - Player text given after command verb.
 * Returns	: int - 1 (success) / 0 (failure)
 */
public nomask int
do_stand(string str)
{
    object ob;
    mixed *tmp;

    if (!strlen(str) || !IN_ARRAY(str, stand_args))
    {
	notify_fail(capitalize(query_verb()) +" "+
	    implode(stand_args, "/") +", maybe?\n");
	return 0;
    }

    /* They aren't sitting here, bail. */
    if (!pointerp(tmp = m_seated[TP]))
    {
	ss_already_stand();
	return 0;
    }

    /* Possibly deny the stand attempt. */
    if (!no_deny && deny_stand())
	return 2;

    /* Make player visible. */
    TP->unset_no_show_composite();

    if ((tmp[SS_LSTATE] == SS_IN_LAP) &&
	objectp(ob = tmp[SS_PLAYER]))
    {
	/* We were in a lap, leave it. */
	m_seated[ob] = ({ tmp[SS_STATE], SS_NO_LAP, 0 });
        ss_stand_lap(ob);
    }
    else
    {
        ss_stand();

	if (objectp(ob = tmp[SS_PLAYER]))
	{
	    /* Our lap was taken when we stood. */
	    if (shift_seat)
	    {
		/* Let them take over a cushion. */
		taken += 1;
		m_seated[ob] = ({ SS_NORMAL, SS_NO_LAP, 0 });
                ss_shift_seat(ob);
	    }
	    else
	    {
		/* So mean, kick 'em to the curb. */
		ob->unset_no_show_composite();
		m_delkey(m_seated, ob);
                ss_dumped(ob);
	    }
	}

	/* Update number of taken seats. */
	switch(tmp[SS_STATE])
	{
	case SS_NORMAL:
	    taken -= 1;
	    break;
	case SS_STRETCH:
	    taken -= lay_num;
	    break;
	}
    }

    /* Cleanup settings. */
    m_delkey(m_seated, TP);

    /* Update properties. */
    update_props(-(TP->query_prop(OBJ_I_WEIGHT)),
		 -(TP->query_prop(OBJ_I_VOLUME)));

    if (!m_sizeof(m_seated))
	cur_weight = cur_volume = 0;

    /* If called by the shadow, let it remove itself safely. */
    if (TP->query_seating_shadow() != calling_object(0))
	rem_seat_shadow(TP);

    return 1;
}

/*
 * Function name: do_not_deny
 * Description	: Function to force us not to deny people standing.
 * 		  Called during destruct, quit and linkdeath events.
 */
public nomask void
do_not_deny(void)
{ 
    if (no_deny)
	no_deny = 0;
    else
	no_deny = set_alarm(0.5, 0.0, &do_not_deny());
}

/*
 * Masked to add our commands to people.
 * See: sman /std/object init
 */
public void
init(void)
{
    int ix, sz;

    ::init();

    /* Can't sit while carrying. */
    if (living(environment()))
	return;

    /* These are the normal sitting commands. */
    for (ix = 0, sz = sizeof(sit_cmds); ix < sz; ix++)
	add_action(do_seat, sit_cmds[ix]);

    /* These are the commands to stand up. */
    for (ix = 0, sz = sizeof(stand_cmds); ix < sz; ix++)
	add_action(do_stand, stand_cmds[ix]);

    /* These are added only if we allow stretching out. */
    if (lay_num && (lay_num <= max_seat))
    {
	for (ix = 0, sz = sizeof(lay_cmds); ix < sz; ix++)
	    add_action(do_seat, lay_cmds[ix]);
    }
}

/*
 * Masked as a failsafe for the object getting removed with
 * seated players upon it.
 * See: sman /std/object remove_object
 */
public void
remove_object(void)
{
    /* Obtain list of valid seaters. */
    object *whom = m_indexes(m_seated);

    /* Do not deny. */
    no_deny = 1;

    /* We do this quick-n-dirty to save time. */
    whom->catch_tell("As the "+ short() +" disappears, you stand up.\n");
    whom->unset_no_show_composite();
    map(whom, rem_seat_shadow);

    /* Remove our tracking information. */
    remove_seating_info(environment());

    /* Pass along removal request. */
    ::remove_object();
}

/*
 * Masked to allow dynamically changing visibility.
 * See: sman /std/object query_no_show_composite
 */
public int
query_no_show_composite(void)
{
    if (visible == 1)
	return !!taken;
    else
	return !visible;
}

/*
 * Show our seated status.
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if (!taken)
	return "";

    return seat_desc();
}

/*
 * Masked to show various status information about this object.
 * See: sman /std/object stat_object
 */
public string
stat_object(void)
{
    string str = ::stat_object();

    str += sprintf(
	"Seat Weight: %,7d, \tSeat Volume: %,7d\n" +
	"Max seats: %9d, \tSeats taken: %7d\n" +
	"Allow stretch: %5s, \tNum to stretch: %4d\n" +
	"Kinky seats: %7s, \tShifting seats: %4s\n" +
	"Portable: %10s, \tVisibility: %8s\n",
	seat_weight, seat_volume, max_seat, taken,
	(lay_num ? "yes" : "no"), lay_num,
	(allow_kinky ? "yes" : "no"), (shift_seat ? "yes" : "no"),
	(portable ? "yes" : "no"),
	(visible ? (visible > 1 ? "Always" : "Dynamic") : "Never")
    );

    return str;
}
