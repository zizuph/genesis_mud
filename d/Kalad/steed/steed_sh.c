/*
 * steed_sh.c
 *
 * Rider's shadow for riding steed.c around.
 *
 * Copyright by Wout de Zeeuw, Fysix@Genesis, May 1997
 *
 * Revision History:
 * ----------------
 * - Last modified:  15 Dec 1997
 *
 * - Modifed move_living to allow other steeds to follow the team
 *   Trofast Dec 1999
 *
 * - Recoded and cleaned up, Lucius
 */

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define COMPAT /* This should allow to work with old code */

static object mount;			/* The steed object riding.	*/
static string rider_m_in, rider_m_out;	/* Movement messages		*/

/*
 * Function name: set_steed_object
 * Description:   Called from steed when mounting.
 *		  Configures some base values for the riders.
 * Arguments:     object - the steed object
 */
public void
set_steed_object(object ob)
{
    mount = ob;

    /* Description is controlled by the steed. */
    shadow_who->set_no_show_composite(1);

    /* Set the movement messages assigned from the steed. */
    rider_m_in  = mount->query_rider_m_in(shadow_who);
    rider_m_out = mount->query_rider_m_out(shadow_who);
}

/*
 * Function name: query_steed_object
 * Description	: What steed is assigned to this rider?
 * Argumentes	: none
 * Returns	: object - the assigned steed
 */
public nomask object
query_steed_object()
{
    return mount;
}

/*
 * Function name: query_valid_steed_shadow
 * Description	: Is this a true and valid steed shadow?
 * Arguments	: none
 * Returns	: int 1 - yes this is.
 */
public nomask int
query_valid_steed_shadow()
{
    return 1;
}

/*
 * - query_m_in()
 * - query_m_out()
 *
 * Our masked movement messages.
 */
public nomask string
query_m_in()
{
    return rider_m_in;
}

public nomask string
query_m_out()
{
    return rider_m_out;
}

/*
 * Function name: steed_check_team
 * Description	: Check to see if a teammember should get moved
 *		  along with the steed.
 * Arguments	: object - teammember
 * Returns	: int - 1, safe to move | 0, don't move.
 */
private nomask int
steed_check_team(object ob)
{
    object tmp;

    if (environment(ob) != environment(shadow_who))
    {
	return 0;
    }

    if (!shadow_who->check_seen(ob))
    {
	return 0;
    }

    if (objectp(tmp = ob->query_prop(LIVE_O_STEED)))
    {
	if (tmp->query_steed_driver() == ob)
	{
	    return 1;
	}
#ifdef COMPAT
	else if (tmp->query_driver() == ob)
	{
	    return 1;
	}
#endif
	return 0;
    }

    return 1;
}

/*
 * Function name: steed_move_team
 * Description:   Move a member of a team in one direction.
 *		  Can't use follow leader as we may not be
 *		  the team leader.
 * Arguments:     object - member.
 *		  string - The command.
 * Returns:       void
 */
private nomask void
steed_move_team(object ob, string com)
{
    set_this_player(ob);
    ob->command("$" + com);
}

/*
 * Masked to prevent additional riders from controlling
 * the steed in a team.
 */
public nomask void
follow_leader(string com) 
{
    object tmp;

    /* Only accept this call if we are called from our team-leader. */
    if ((tmp = previous_object()) != shadow_who->query_leader())
    {
	return;
    }

    if (objectp(tmp = tmp->query_steed_object()))
    {
	if ((tmp == mount) &&
	  (shadow_who != tmp->query_steed_driver()))
	{
	    return;
	}
    }
#ifdef COMPAT
    else if (objectp(tmp = tmp->query_steed()))
    {
	if ((tmp == mount) &&
          (shadow_who != tmp->query_driver()))
        {
            return;
        }
    }
#endif

    set_this_player(this_object());

    /* We use a call_other since you are always allowed to force yourself.
     * That way, we will always be able to follow our leader.
     */
    this_object()->command("$" + com);
}

/*
 * Function name: remove_steed_shadow
 * Description:   removes this steed shadow.
 */
public void
remove_steed_shadow()
{
    remove_shadow();
}

/*
 * Function name: restore_rider
 * Description:   Restores the rider's no_show_composite.
 */
public void
restore_rider()
{
    if (!objectp(shadow_who))
	return;

    shadow_who->set_no_show_composite(0);
}

/*
 * Function name: move_living
 * Description:   Shadow the rider's move_living function in order to 
 *   co-move the steed. Functions moves the rider, then the steed,
 *   then the co-riders, and last the rest of the team.
 *   When you want to call the original move_living 
 *   without bothering about the steed, call move_living_old in the player. 
 *   You should do sanity checks yourself then though!
 * Returns: 8 if the steed cannot go there
 *          9 if the rider is not the driver
 *          10 the steed is too tired to move
 */
public varargs int
move_living(string how, mixed dest, int dont_follow, int no_glance)
{
    int    rval, res;
    object *team, env;
    string vb, com;

    rval = mount->steed_check_dest(dest, shadow_who, how);

    if (how == "X")
    {
	if (!rval || mount->query_steed_no_trans() ||
	  (sizeof(mount->query_steed_riders()) > 1))
	{
	    mount->steed_do_dismount(shadow_who, 1, 1);
	    rval = shadow_who->move_living(how, dest, dont_follow, no_glance);
	    remove_steed_shadow();
	    /* Should not be reached.. */
	    return rval;
	}
	else
	{
	    dont_follow = 1;
	}
    }

    if (!rval)
    {
	mount->st_hook_invalid_dest(shadow_who, how);
	return 8;
    }

    team = shadow_who->query_team();
    if (pointerp(shadow_who->query_steed_follow()))
	team += shadow_who->query_steed_follow();

    if (team && !dont_follow)
    {
	env  = environment(shadow_who);
	vb   = query_verb();
	team = filter(team, steed_check_team);
    }

    rval = shadow_who->move_living(how, dest, 1, no_glance);

    if (!rval)
    {
	res = mount->move_living(how, dest, 1, 1);

	if (res)
	{
	    mount->st_hook_invalid_dest(shadow_who, how);
	    return res;
	}

	env = mount->query_prop(LIVE_O_LAST_ROOM);
	env->add_prop(ROOM_S_DIR, ({ how, "horse"}));

	if (!dont_follow && sizeof(team))
	{
	    if (!strlen(vb))
	    {
		com = (sizeof(explode(how, " ")) == 1 ? how : "");
	    }
	    else
	    {
		com = env->query_dircmd();
		com = (com ? vb + " " + com : vb);
	    }

	    map(team, &steed_move_team(, com));
	}
    }

    if (environment(shadow_who) != environment(mount))
    {
	mount->steed_do_dismount(shadow_who, 1, 1);
	remove_steed_shadow();
    }

    return rval;
}

/*
 * Function name: move_living_old
 * Description:   Calls original move_living function, is called by
 *                the steed to make its riders follow it. Might give
 *                unexpected results when not used correctly. Should probably
 *                never be called by any other object than the steed.
 * Arguments:     see move_living
 * Returns:       see move_living
 */
public nomask varargs int
move_living_old(string how, mixed dest, int dont_follow, int no_glance)
{
    return shadow_who->move_living(how, dest, dont_follow, no_glance);
}

/* Function name: allow_skill_redirect
 * Description:   Determine if we should allow the query_skill
 *		  call to be redirected to the steed.
 * Arguments:     object - the calling object
 * Returns:       int - 1, yes allow it | 0, no use riders.
 */
public int
allow_skill_redirect(object caller)
{
    return (query_verb() != "skills" && query_verb() != "skillstat");
}

/*
 * Masked, some skills should be based on the steeds skills,
 * not the riders.
 */
public int
query_skill(int num)
{
    if (allow_skill_redirect(calling_object()))
    {
	if (member_array(num, mount->query_steed_redir_skills()) >= 0)
	{
	    return mount->query_skill(num);
	}
    }

    return shadow_who->query_skill(num);
}

/*
 * Masked, when mounted, the steed should take 75% of the fatigue.
 * As represented by the basic random(4).
 */
public void
add_fatigue(int num)
{
    if ((num < 0) && random(4) && calling_object()->query_prop(ROOM_I_IS))
    {
	mount->add_fatigue(num);
    }
    else
    {
	shadow_who->add_fatigue(num);
    }
}

/*
 * Masked and made private for safety, security concerns.
 */
private void
remove_shadow()
{
    restore_rider();
    ::remove_shadow();
}

/*
 * - attacked_by()
 * - attack_object()
 *
 * Masked, When attacked or attacking, we must dismount if the steed is 
 * not trained for combat.
 */
public void
attacked_by(object ob)
{
    if (!mount->query_steed_allow_combat())
    {
	mount->steed_do_dismount(shadow_who, 1, 1);
	shadow_who->attacked_by(ob);
	remove_steed_shadow();
    }
    else
    {
	shadow_who->attacked_by(ob);
    }
}

public void
attack_object(object ob)
{
    if (!mount->query_steed_allow_combat())
    {
	mount->steed_do_dismount(shadow_who, 1, 1);
	shadow_who->attack_object(ob);
	remove_steed_shadow();
    }
    else
    {
	shadow_who->attack_object(ob);
    }
}

/*
 * Masked, we died, get off the horse first!
 */
public void
do_die(object killer)
{
    if ((shadow_who->query_hp() > 0) ||
      shadow_who->query_wiz_level() ||
      shadow_who->query_ghost())
    {
	return;
    }

    if (objectp(mount))
	mount->steed_do_dismount(shadow_who, 1, 1);

    restore_rider();
    shadow_who->do_die(killer);
    ::remove_shadow();
}

/*
 * Masked, we have to unmount and restore the rider before
 * we dest them.
 */
public void
remove_object()
{
    if (objectp(mount))
	mount->steed_do_dismount(shadow_who, 1, 1);  

    restore_rider();
    ::remove_object();
}

/*
 * Function name: linkdeath_hook
 * Description:   dismount player when linkdieing.
 * Arguments:     int 1 for linkdeath, 0 for revive
 */
public void
linkdeath_hook(int i)
{
    if (i == 1)
    {
	if (objectp(mount))
	    mount->steed_do_dismount(shadow_who, 1, 1);

	restore_rider();
	mount->move_living("M", mount->query_prop(LIVE_O_LAST_ROOM), 1, 1);
	shadow_who->linkdeath_hook(i);

	::remove_shadow();
    }
    else
    {
	shadow_who->linkdeath_hook(i);
    }
}

/*
 * Function name: rider_check_dest
 * Description:   Check if the player can go somewhere. This function
 *                has to handle message itself when the player cannot go
 *                to the specified destination.
 * Arguments:     mixed destination
 *                [string where_to]: e.g. "go north", "board the ship".
 *                   If "M" is passed give no fail messages.
 *                   If omitted "go there" will be substituted.
 * Returns:       int 1 if it's ok to move
 *                otherwise error code according to the 
 *                steed_check_dest code in the steed.
 */
public varargs int
rider_check_dest(mixed dest, string where)
{
    return mount->steed_check_dest(dest, shadow_who, where);
}

/*
 * Function name: query_cannot_board_ship
 * Description:   Can a player not board? Called by the ship object.
 * Arguments:     mixed destination room
 * Returns:       int 1 if unable to board
 */
public int
query_cannot_board_ship(mixed dest)
{
    if (!rider_check_dest(dest, "board"))
	return 1;
    else
	return shadow_who->query_cannot_disembark_ship(dest);
}

/*
 * Function name: query_cannot_disembark_ship
 * Description:   Can a player not disembark? Called by the deck object.
 * Arguments:     mixed destination room
 * Returns:       int 1 if unable to disembark
 */
public int
query_cannot_disembark_ship(mixed dest)
{
    if (!rider_check_dest(dest, "disembark"))
	return 1;
    else
	return shadow_who->query_cannot_disembark_ship(dest);
}

/*
 * - set_m_in()
 * - set_m_out()
 *
 * Masked, to prevent people from changing the mounted move messages.
 */
public void
set_m_in(string s)
{
/*
    shadow_who->set_m_in(s);
 */
}

public void
set_m_out(string s)
{
/*
    shadow_who->set_m_out(s);
 */
}


/*
 * Compability functions for use with olde steeds.
 */
#ifdef COMPAT

public object
query_steed()		{ return query_steed_object(); }

public nomask int
is_steed_shadow()	{ return query_valid_steed_shadow(); }

#endif


