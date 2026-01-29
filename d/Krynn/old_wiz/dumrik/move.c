/*
 * /std/living/move.c
 *
 * This is a subpart of living.c
 * All movement related routines are coded here.
 *
 * Revision history:
 * 12-94 Wizball@Muddy Waters recoded this object and made it 20% faster.
 */
 
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <std.h>
 
/*
 * Function name: move_reset
 * Description  : Reset the move module of the living object.
 */
static nomask void
move_reset()
{
    this_object()->set_m_in(LD_ALIVE_MSGIN);
    this_object()->set_m_out(LD_ALIVE_MSGOUT);
 
    this_object()->set_mm_in(LD_ALIVE_TELEIN);
    this_object()->set_mm_out(LD_ALIVE_TELEOUT);
}
 
/*
 * Function name: move_living
 * Description:   Posts a move command for a living object somewhere. If you
 *                have a special exit like 'climb tree' you might want to
 *                use set_dircmd() and set it to 'tree' in the room to allow
 *                teammembers to follow their leader.
 * Arguments:     how:      The direction of travel, like "north".
 *                          "X" for teleportation
 *                          "M" if you write leave and arrive messages yourself.
 *                to_dest:  Destination
 *                dont_follow: A flag to indicate group shall not follow this
 *                          move if this_object() is leader
 *                no_glance: Don't look after move.
 *
 * Returns:       Result code of move:
 *                      0: Success.
 *
 *                      3: Can't take it out of it's container.
 *                      4: The object can't be inserted into bags etc.
 *                      5: The destination doesn't allow insertions of objects.
 *                      7: Other (Error message printed inside move() func)
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int    index, size, invis;
    object *team, *drag, env, oldtp;
    string vb, com, msgout, msgin;
    mixed msg;
    
    oldtp = this_player();
 
    if (!objectp(to_dest))
    {
	msg = LOAD_ERR(to_dest);
	to_dest = find_object(to_dest);
    }
    
    if (stringp(msg))
    {
	if (!environment(this_object()))
	{
	    tell_object(this_object(), "PANIC Move error: " + msg);
	    to_dest = this_object()->query_default_start_location();
	    msg = LOAD_ERR(to_dest);
	    to_dest = find_object(to_dest);
	}
	else
	{
	    tell_object(this_object(), msg);
	    SECURITY->log_loaderr(to_dest, environment(this_object()), how,
		previous_object(), msg);
	    return 7;
	}
    }
 
    if (!to_dest->query_prop(ROOM_I_IS))
    {
	return 7;
    }
 
    if (!how)
    {
	return move(to_dest, 1);
    } 

    if (how == "M") 
    {
	msgin = 0;
	msgout = 0;
    } 
    else if (how == "X") 
    {
	msgin = this_object()->query_mm_in() + "\n";
	msgout = this_object()->query_mm_out() + "\n";
    }
    else if (query_prop(LIVE_I_SNEAK)) 
    {
	msgin = explode(this_object()->query_m_in(), ".")[0] +
	    " sneaking. " + "\n";
	msgout = "sneaks " + how + ".\n";
    }
    else 
    {
	msgin = this_object()->query_m_in() + " " + "\n";
	msgout = this_object()->query_m_out() + " " + how + ".\n";
    }

    invis = query_prop(OBJ_I_INVIS);
                                    
    set_this_player(this_object());
 
    if (env = environment(this_object()))
    {
	/* Update the last room settings. */
	add_prop(LIVE_O_LAST_ROOM, env);
	add_prop(LIVE_S_LAST_MOVE, (vb = query_verb()));
 
	/* Update the hunting status */
	this_object()->adjust_combat_on_move(1);

	/* Leave footprints. */
 	if (!env->query_prop(ROOM_I_INSIDE) &&
	    (env->query_prop(ROOM_I_TYPE) == ROOM_NORMAL) &&
	    !query_prop(LIVE_I_NO_FOOTPRINTS))
	{
	    env->add_prop(ROOM_S_DIR, ({ how, query_race_name() }) );
	}

	/* Report the departure. */                     
	if (msgout)
	{
	    if (invis)
	    {
		say( ({ "(" + METNAME + ") " + msgout,
		    TART_NONMETNAME + " " + msgout,
		    "" }) );
	    }
	    else
	    {
		say( ({ METNAME + " " + msgout,
		    TART_NONMETNAME + " " + msgout,
		    "" }) );
	    }
	}
    }    

    if (!query_prop(LIVE_I_SNEAK))
    {
	remove_prop(OBJ_I_HIDE); 
    }
    else
    {
	remove_prop(LIVE_I_SNEAK);
    }

    if (index = move(to_dest)) 
    {
	return index;
    }

    if (msgin)
    {
	if (invis)
	{
	    say( ({ "(" + METNAME + ") " + msgin,
		ART_NONMETNAME + " " + msgin,
		"" }) );
	}
	else
	{
	    say( ({ METNAME + " " + msgin,
		ART_NONMETNAME + " " + msgin,
		"" }) );
	}
    }

    /* Take a look at the room you've entered, before the combat adjust.
     * Only interactive players bother to look. Don't waste our precious
     * CPU-time on NPC's.
     */
    if (this_object()->query_see_special_msg() && !no_glance)
    {
	this_object()->do_glance(this_object()->query_brief());
    }
 
    /* See is people were hunting us or if we were hunting people. */
    this_object()->adjust_combat_on_move(0);
 
    if (sizeof(drag = query_prop(TEMP_DRAGGED_ENEMIES)))
    {
	index = -1;
	size = sizeof(drag);

	while(++index < size)
	{
	    tell_room(environment(drag[index]), QCTNAME(drag[index]) +
		" leaves following " + QTNAME(this_object()) + ".\n",
		drag[index]);
	    drag[index]->move_living("M", to_dest);
	    tell_room(environment(drag[index]), QCTNAME(drag[index]) +
		" arrives following " + QTNAME(this_object()) + ".\n",
		({drag[index], this_object()}));
	    this_object()->catch_msg(QCTNAME(drag[index]) +
				     " arrives following you.\n");
	    
	}
	remove_prop(TEMP_DRAGGED_ENEMIES);
    }
                               
    if (!dont_follow &&
	stringp(how) &&
	(size = sizeof(team = query_team())))
    {
	/* Command for the followers if this is a leader. */
        if (!strlen(vb))
        {
	    if (sizeof(explode(how, " ")) == 1)
	    {
		com = how;
	    }
	    else
	    {
		com = "";
	    }
        }
        else if (com = env->query_dircmd())
	{
	    com = vb + " " + com;
	}
	else
	{
	    com = vb;
	}

	/* Move the present team members. */
	index = -1;
	while(++index < size)
	{
	    if ((environment(team[index]) == env) &&
		this_object()->check_seen(team[index]))
	    {
		team[index]->follow_leader(com);
	    }
	}
    }
                                   
    set_this_player(oldtp);

    return 0;
}

/*
 * Function name: follow_leader
 * Description  : If the leader of the team moved, follow him/her.
 * Arguments    : string com - the command to use to follow the leader.
 */
public void
follow_leader(string com) 
{
    set_this_player(this_object());

    /* We use a call_other since you are always allowed to force yourself.
     * That way, we will always be able to follow our leader.
     */
    this_object()->command("$" + com);
}

/*
 * Function name: reveal_me
 * Description  : Reveal me unintentionally.
 * Arguments    : int tellme - true if we should tell the player.
 * Returns      : int - 1 : He was hidden, 0: He was already visible.
 */
public nomask int
reveal_me(int tellme)
{
    object *list;
    int index, size;

    if (!query_prop(OBJ_I_HIDE))
    {
	return 0;
    }

    if (tellme)
    {
	this_object()->catch_msg("You are no longer hidden.\n");
    }
 
    list = FILTER_LIVE(all_inventory(environment()) - ({ this_object() }) );
    remove_prop(OBJ_I_HIDE);

    index = -1;
    size = sizeof(list);
    while(++index < size)
    {
	if (check_seen(list[index]))
	{
	    tell_object(list[index],
		this_object()->query_The_name(list[index]) +
		" decides to come out of hiding.\n");
	}
	else
	{
	    tell_object(list[index], "You are startled to find " +
		this_object()->query_art_name(list[index]) +
		" suddenly standing next to you!\n");
	}
    }

    return 1;
}
