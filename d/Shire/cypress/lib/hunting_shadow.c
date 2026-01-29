/*
 * /d/Gondor/common/lib/follow_shadow.c
 *
 * Copied from /d/Krynn/open/follow.c
 * Modified by Olorin, January 1997
 *
 * Modified by Igneous, January 1998
 *
 * Copied from Shire and modified for Mysteria
 * -- Finwe, May 2001
 *
 * Start by a call to hunt().
 *
 * The functions remove_victim(object who) is called in the follower
 * if the following terminates for any reason.
 * The specific hooks are:
 * fail_see(object who)         - the follower cannot see the 'who'
 *                                anymore;
 * stopped_hunting(object who)  - the follower does not hunt who
 *                                anymore;
 * fail_follow(object who)      - the follower was unable to follow
 *                                the victim, either because the
 *                                victim teleported or because the
 *                                follower was unable to use the exit
 *                                the vicitm used. 
 * Modification log:
 *
 *

 */
#pragma strict_types

inherit "/std/shadow.c";

#include <stdproperties.h>

//#define DEBUG 1

#if DEBUG
#define DEBUG_MSG(x)    find_player("finwe")->catch_tell("FOLLOW: " \
    + (x) + "\n");
#else
#define DEBUG_MSG(x)
#endif

static float   Delay = -1.0;
static int     Follow_stop,
Combat;
static object *Follower = ({ });

/*
 * Function name: set_delay
 * Description:   Set the delay for following.
 * Argument:      Time in seconds.
 */
public void
set_delay(float f)
{
    if (f > 0.0)
	Delay = f;
    else
	Delay = 0.1;
}

/*
 * Function name: add_follower
 * Description:   add another follower to the list
 * Arguments:     object pointer to the follower
 */
public void
add_follower(object follower)
{
    Follower -= ({ follower });
    Follower += ({ follower });
}

/*
 * Function name: hunt
 * Description:   Initiate the following,
 *                add the shadow to the victim.
 * Arguments:     object who - the victim
 *                object who - the npc following the victim
 *                int combat - if true, follow only during combat
 *                float delay - Time in which the hunting delay is
 */
public varargs void
hunt(object who, object follower, int combat = 1, float delay = 0.1)
{
    if (who->query_hunting_shadow())
    {
	who->add_follower(follower);
	who->set_delay(delay);
	set_alarm(0.0,0.0,remove_shadow);
	return;
    }
    Follower += ({ follower });
    Combat = combat;
    Delay = delay;

    shadow_me(who);
}

/*
 * Function name: follow_move
 * Description:   Delayed following.
 * Argument:      cmd - direction command.
 */
public void
follow_move(string cmd)
{
    object *old;

    Follower->command("$" + cmd);
    Follow_stop = 0;

    old = Follower;
    Follower = filter(Follower, objectp @ &present( , environment(shadow_who)));
    old -= Follower;
    if (pointerp(old) && sizeof(old))
    {
	DEBUG_MSG("failed to follow");
	old->fail_follow(shadow_who);
	old->remove_victim(shadow_who);
    }

    if (!pointerp(Follower) || !sizeof(Follower))
    {
	DEBUG_MSG("remove_shadow: no Follower");
	set_alarm(0.0, 0.0, remove_shadow);
    }
}

/*
 * Function name: move_living
 * Description:   Shadow of move_living to make the follower follow
 *                the victim.
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
    object *old;
    string  cmd;
    int     i,
    s,
    flag;

    if (!(cmd = environment(shadow_who)->query_dircmd()))
	cmd = query_verb();
    else
	cmd = query_verb() + " " + cmd;

    flag = shadow_who->move_living(how, to_dest, dont_follow,
      no_glance);

    // We stop following if the Follower doesn't exist anymore or
    // if the Follower cannot see the victim anymore or, if the Combat
    // flag is set, if the Follower doesn't hunt the shadowed living
    // anymore: 
    Follower = filter(Follower, objectp);
    if (Follow_stop || !pointerp(Follower) || !sizeof(Follower))
    {
	DEBUG_MSG("remove_shadow: no Follower");
	set_alarm(0.0, 0.0, remove_shadow);
	return flag;
    }

    Follow_stop = 1;

    old = Follower;
    Follower = filter(Follower, &->can_see_in_room());
    Follower = filter(Follower, &shadow_who->check_seen());
    old -= Follower;

    if (pointerp(old) && sizeof(old))
    {
	DEBUG_MSG("cannot see");
	old->fail_see(shadow_who);
	old->remove_victim(shadow_who);
    }

    if (!pointerp(Follower) || !sizeof(Follower))
    {
	DEBUG_MSG("remove_shadow: no Follower");
	set_alarm(0.0, 0.0, remove_shadow);
	return flag;
    }

    if (Combat)
    {
	old = Follower;
	Follower = filter(Follower, &operator(==)(shadow_who) @ &->query_enemy());
	old -= Follower;
	if (pointerp(old) && sizeof(old))
	{
	    DEBUG_MSG("stopped hunting");
	    old->stopped_hunting(shadow_who);
	    old->remove_victim(shadow_who);
	}

	if (!pointerp(Follower) || !sizeof(Follower))
	{
	    DEBUG_MSG("remove_shadow: no Follower");
	    set_alarm(0.0, 0.0, remove_shadow);
	    return flag;
	}
    }

    if (Delay > 0.0)
    {
	set_alarm(Delay, 0.0, &follow_move(cmd));
	return flag;
    }

    Follower->command("$" + cmd);
    Follow_stop = 0;

    old = Follower;
    Follower = filter(Follower, objectp @ &present( , environment(shadow_who)));
    old -= Follower;
    if (pointerp(old) && sizeof(old))
    {
	DEBUG_MSG("failed to follow");
	old->fail_follow(shadow_who);
	old->remove_victim(shadow_who);
    }

    if (!pointerp(Follower) || !sizeof(Follower))
    {
	DEBUG_MSG("remove_shadow: no Follower");
	set_alarm(0.0, 0.0, remove_shadow);
    }

    return flag;
}

/*
 * Function name: query_follower
 * Description:   return a list of all objects following shadow_who
 * Returns:       the list.
 */
public object *
query_follower()
{
    return Follower;
}

/*
 * Function name: remove_follow_shadow
 * Description:   remove the shadow, stop following.
 */
public void
remove_follow_shadow()
{
    destruct();
}

int
query_hunting_shadow()
{
    return 1;
}
