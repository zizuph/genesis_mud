/*
 * lead_sh.c
 *
 * Shadow for leading steeds
 *
 * Copyright by Wout de Zeeuw, Fysix@Genesis, August 1997
 *
 * Revision History:
 * ----------------
 *
 * - Lucius, code cleanup for steed rewrite.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

static object *following = ({ });

/*
 * Masked for safety and private for security concerns.
 */
private void
remove_shadow()
{
    following->do_unlead(shadow_who);
    ::remove_shadow();  
}

/*
 * Function name: remove_lead_shadow
 * Description:   Call this function to remove this shadow.
 */
public void
remove_lead_shadow()
{
    remove_shadow();
}

/*
 * Function name: add_steed_follow
 * Description:   Has to be called to initialize this shadow.
 *                Adds a steed to the shadowee that follows him.
 * Arguments:     object - the steed object
 */
public int
add_steed_follow(object ob)
{
    if (member_array(ob, following) >= 0)
	return 0;

    if (sizeof(following) >= 3)
	return 0;

    following -= ({ 0 });
    following += ({ ob });
    return 1;
}

/*
 * Function name: remove_steed_follow
 * Description:   Let a steed stop following
 * Arguments:     object - the following steed object
 */
public int
remove_steed_follow(object ob)
{
    following -= ({ 0 });
    following -= ({ ob });

    if (!sizeof(following))
	remove_lead_shadow();

    return 1;
}

/*
 * Function name: query_steed_follow
 * Description:   Which are all steeds following the shadowee?
 * Returns:       object *
 */
public object *
query_steed_follow()
{
    return ({}) + following;
}

/*
 * Function name: query_leading_steed
 * Description:   Is shadow_who leading one or more steeds?
 * Returns:       int 1
 */
public int
query_leading_steed()
{
    return 1;
}

/*
 * Function name: steed_check_followers
 * Description:   Check that the follower is where the rider is.
 * Arguments:     object - The follower object to check.
 * Returns:       Result of check. 1/0.
 */
private nomask int
steed_check_followers(object ob)
{
    if (environment(ob) == environment(shadow_who))
    {
	if (shadow_who->check_seen(ob))
	{
	    return 1;
	}
    }

    return 0;
}

/*
 * Function name: steed_move_followers
 * Description:   Move the following steeds
 * Arguments:     ob - A follower to move.
 *                com - The command the leader gave
 * Returns:       Success of move.
 */
private nomask int
steed_move_followers(object ob, string com)
{
    return (int)ob->command("$" + com);
}

/*
 * Function name: move_living
 * Description:   Shadow the rider's move_living function in order to 
 *   co-move the following steeds.
 *   Functions moves the leader, then the steeds.
 *   When you want to call the original move_living 
 *   without bothering about the steed, call move_living_old in the player. 
 */
public varargs int
move_living(string how, mixed dest, int dont_follow, int no_glance)
{
    int    rval;
    string vb, com;
    object env, *followers;

    if (!sizeof(following))
    {
	shadow_who->move_living(how, dest, dont_follow, no_glance);
	::remove_shadow();
    }

    env = environment(shadow_who);
    vb  = query_verb();

    followers = filter(following, steed_check_followers);

    rval = shadow_who->move_living(how, dest, dont_follow, no_glance);

    if (!rval && how != "X" && !dont_follow)
    {
	if (!strlen(vb))
	{
	    if (sizeof(explode(how, " ")) == 1)
		com = how;
	    else
		com = "";
	}
	else if (com = env->query_dircmd())
	{
	    com = vb + " " + com;
	}
	else
	{
	    com = vb;
	}

	if (sizeof(followers))
	{
	    map(followers, &steed_move_followers(, com));
	}
    }

    return rval;
}

/*
 * Function name: move_living_old
 * Description:   Calls original move_living function.
 * Arguments:     see move_living
 * Returns:       see move_living
 */
public varargs int
move_living_old(string how, mixed dest, int dont_follow, int no_glance)
{
    return shadow_who->move_living(how, dest, dont_follow, no_glance);
}

