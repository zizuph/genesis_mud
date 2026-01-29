/*
    /std/living/move.c

    This is a subpart of living.c
    All movement related routines are coded here.

    This file is inherited into living.c
*/

#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <std.h>

static string in_move; /* Dir we are moving in */

/*
 * Prototypes
 */
static int glance();

public void
transmsg_reset()
{
    this_object()->set_m_in(LD_ALIVE_MSGIN);
    this_object()->set_m_out(LD_ALIVE_MSGOUT);

    this_object()->set_mm_in(LD_ALIVE_TELEIN);
    this_object()->set_mm_out(LD_ALIVE_TELEOUT);
}    

/*
 * Function name: move_reset
 * Description:   Reset the move module of the living object.
 * Arguments:	  arg: Reset argument.
 */
static nomask void
move_reset()
{
    in_move = 0;
    transmsg_reset();
    add_action("arrive", "arrive");
    add_action("depart", "depart");
    add_action("glance", "glance");
}

/*
 * Function name: move_living
 * Description:   Posts a move command for a living object somewhere. If you
 *		  have a special exit like 'climb tree' you might want to
 *		  use set_dircmd() and set it to 'tree' in the room to allow
 *		  teammembers to follow their leader.
 * Arguments:	  how:      The direction of travel, like "north".
 *			    "X" for teleportation
 *			    "M" if you write leave and arrive messages yourself.
 *                to_dest:  Destination
 *                no_glance: Don't look after move.
 *		  dont_follow: A flag to indicate group shall not follow this
 *			    move if this_object() is leader
 *
 * Returns:       Result code of move:
 *			0: Success.
 *
 *			3: Can't take it out of it's container.
 *			4: The object can't be inserted into bags etc.
 *			5: The destination doesn't allow insertions of objects.
 *                      7: Other (Error message printed inside move() func)
 */
public nomask varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int             i;
    object          *team, *drag, env;
    string	    vb, com;

    i = LOAD_ERR(to_dest);
    if (stringp(i))
    {
	if (!environment(this_object()))
	{
	    write("PANIC Move error: " + i);
	    to_dest = this_object()->query_default_start_location();
	    i = LOAD_ERR(to_dest);
	}
	else
	{
	    write(i);
	    SECURITY->log_loaderr(to_dest, environment(this_object()), how,
				  previous_object(), i);
	    return 7;
	}
    }

    if (!objectp(to_dest))
	to_dest = find_object(to_dest);

    if (!to_dest->query_prop(ROOM_I_IS))
	return 7;

    if (!how)
	return move(to_dest, 1);

    in_move = how;

    team = query_team();
    if (team)
	team = filter(team, "check_team", this_object());

    if (env = environment(this_object()))
    {
	/*
 	 * Update the last room settings
	 */
	change_prop(LIVE_O_LAST_ROOM, env);
	change_prop(LIVE_S_LAST_MOVE, (vb = query_verb()));

	/*
	 * Command for the followers if this is a leader
	 */
	if (!strlen(vb))
	{
	    if (sizeof(explode(how, " ")) == 1)
		com = how;
	    else
	        com = "";
	}
	else if (com = env->query_dircmd())
	    com = vb + " " + com;
	else
	    com = vb;

	/*
	 * Update the hunting status
	 */
	adjust_combat_on_move(1);

	/*
	 * Leave footprints if outside and room normal
	 */
	if (!env->query_prop(ROOM_I_INSIDE) &&
	    		env->query_prop(ROOM_I_TYPE) == ROOM_NORMAL)
	    env->change_prop(ROOM_S_DIR, ({ how, query_race_name() }) );

	/*
	 * Report the departure.
	 */
	command("$depart " + in_move);
    }

    /*
     * Transport and announce the arrival.
     */
    if (!query_prop(LIVE_I_SNEAK))
	remove_prop(OBJ_I_HIDE); 
    if (i = move(to_dest)) 
	return i;

    command("$arrive " + in_move);
    remove_prop(LIVE_I_SNEAK); 

    /*
     * Take a look at the room you've entered, before the combat adjust
     */
    if (!no_glance)
	command("$glance");

    /*
     * Hunted/hunting automatic attacks.
     * Callout is used to get the combat starting after you see you have
     * entered the room.
     */
    adjust_combat_on_move(0);

    drag = query_prop(TEMP_DRAGGED_ENEMIES);
    if (sizeof(drag))
    {
	for (i = 0; i < sizeof(drag); i++)
	{
	    tell_room(environment(drag[i]), QCTNAME(drag[i]) +
		      " leaves following " + QTNAME(this_object()) + ".\n", 
                     ({ drag[i], this_object()}));
	    drag[i]->move_living("M", to_dest);
	    tell_room(environment(drag[i]), QCTNAME(drag[i]) +
		      " arrives following " + QTNAME(this_object()) + ".\n", 
                      ({ drag[i], this_object()}));
	}
	remove_prop(TEMP_DRAGGED_ENEMIES);
    }

    if (!dont_follow)
    {
    	if (sizeof(team))
            team = filter(team, "move_team", this_object(), com);
    	if (sizeof(team))
	    this_object()->tell_leader(team, com);
    }

    in_move = 0;

    return 0;
}

/*
 * Function name: check_team
 * Description:   Check that the team is where "I" am.
 * Arguments:     ob - The team object to check.
 * Returns:       Result of check. 1/0.
 */
nomask int
check_team(object ob)
{
    return (environment(ob) == environment(this_object()) && CAN_SEE(ob, this_object()));
}

/*
 * Function name: move_team
 * Description:   Move a member of a team in one direction.
 * Arguments:     ob - A teammember to move.
 * 		  com - The command the leader gave
 * Returns:       Success of move.
 */
nomask int
move_team(object ob, string com)
{
    if (!in_move)
	return 0;

    return (int) ob->follow_leader(com, this_object());
}

/*
 * Function name:   follow_leader
 * Description:     Moves the living to follow the leader. This function
 *                  is called by the leader of a team.
 * Arguments:       how: The sound-string.
 *		    leader: The one we follow
 * Returns:         0 if not called by the team-leader,
 *                  1 or 0 if the command succeeds.
 */
public int
follow_leader(string how, object leader)
{

    if (!strlen(how) || !leader)
	return 0;

    if (leader != this_object()->query_leader())
	return 0;
    else {
	this_object()->command("$" + how);
	if (environment(this_object()) == environment(leader))
	{
	    this_object()->tell_member(leader, how);
	    return 1;
	}
	return 0;
    }
}

/*
 * Function name:   depart
 * Description:     Tell you are departing to surrounding object.
 * Arguments:       how: The sound-string.
 * Returns:         0 if we are moving in a team, 1 if not
 */
static int
depart(string how)
{
    string nmet;
    int invis;

    if (!in_move)
	return 0;
    
    if (!query_m_out())
	set_m_out(F_ALIVE_MSGOUT);
    if (query_ghost())
	nmet = this_object()->query_m_out() + " " + how + "\n";
    else if (how == "X")
	nmet = this_object()->query_mm_out() + "\n";
    else if (how == "M")
	return 1;
    else 
    {
	if (query_prop(LIVE_I_SNEAK))
	    nmet = "sneaks " + how + ".\n";
	else
	    nmet = this_object()->query_m_out() + " " + how + ".\n";
    }
    invis = query_prop(OBJ_I_INVIS);

    say(({  (invis ? "(" : "") + METNAME + (invis ? ") " : " ") + nmet,
		TART_NONMETNAME + " " + nmet,
		"" }));

    return 1;
}

/*
 * Function name:   arrive
 * Description:     Tell you are arriving to surrounding object.
 * Arguments:       how: The sound-string
 * Returns:         0 if we are moving in a team, 1 else
 */
static int
arrive(string how)
{
    string nmet;
    int invis;

    if (!in_move)
	return 0;

    if (!query_m_in())
	set_m_in(F_ALIVE_MSGIN);
    if (query_ghost())
	nmet = this_object()->query_m_in() + "\n";
    else if (how == "X")
	nmet = this_object()->query_mm_in() + "\n";
    else if (how == "M")
	return 1;
    else 
    {
	if (query_prop(LIVE_I_SNEAK))
	    nmet = explode(this_object()->query_m_in(), ".")[0] + " sneaking. " + "\n";
	else
	    nmet = this_object()->query_m_in() + " " + "\n";
    }
    invis = query_prop(OBJ_I_INVIS);

    say(({  (invis ? "(" : "") + METNAME + (invis ? ") " : " ") + nmet,
		ART_NONMETNAME + " " + nmet,
		"" }));

    return 1;
}

/*
 * Function name:   glance
 * Description:     Take a look at the surrounding object.
 * Returns:         True if glance succeeded
 */
static int
glance()
{
    if (!in_move)
	return 0;
    return do_glance(this_object()->query_brief());
}

/*
 * Function name: reveal_me
 * Description:   Reveal me unintentionally.
 * Arguments:     tellme - 1: Tell the player he was revealed. 0: Hush hush.
 * Returns:       1 : He was hidden, 0: He was already visible.
 */
public nomask int
reveal_me(int tellme)
{
    object *list;
    int i;

    if (!query_prop(OBJ_I_HIDE))
	return 0;

    remove_prop(OBJ_I_HIDE);
    if (tellme)
	this_object()->catch_msg("You are no longer hidden.\n");

    list = all_inventory(environment(this_object()));
    list = filter(list, "live_not_me", this_object());
    for (i = 0 ; i < sizeof(list) ; i++)
    {
	if (!CAN_SEE(list[i], this_object()))
	    list[i]->catch_msg("You are startled to find " + QCTNAME(this_object()) + " suddenly standing next to you!\n");
	else
	    list[i]->catch_msg(QCTNAME(this_object()) + " decides to come out of hiding.\n");
    }
    return 1;
}

int
live_not_me(object ob)
{
    if (ob != this_object() && living(ob))
	return 1;
    return 0;
}
