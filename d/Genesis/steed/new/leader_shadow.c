/*
 * leader_shadow.c
 *
 * Shadow for leading steeds
 *
 * Copyright by Wout de Zeeuw, Fysix@Genesis, August 1997
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <stdproperties.h>
#include "steed.h"

// --- Global variables ------------------------------------------------

// The steeds that shadow_who is leading.
static object* steeds = ({ });
// direction the leader is moving to (how from move_living)
static string in_move; 
/** The steed to auto mount when possible. */
static object steed_with_auto_mount;

public void remove_leader_shadow();

/* Function name: add_following_steed
 * Description:   Has to be called to initialize this shadow.
 *                Adds a steed to the shadowee that follows him.
 * Arguments:     object - the steed object
 */
public void
add_following_steed(object o)
{
    steeds -= ({ 0 });
    steeds += ({ o });
}

/* Function name: remove_following_steed
 * Description:   Let a steed stop following
 * Arguments:     object - the following steed object
 */
public void
remove_following_steed(object o)
{
    steeds -= ({ 0 });
    steeds -= ({ o });
    if (!sizeof(steeds))
    {
        remove_leader_shadow();
    }
}

/* Function name: query_following_steeds
 * Description:   Which are all steeds following the shadowee?
 * Returns:       object *
 */
public object*
query_following_steeds()
{
    return steeds;
}

/* Function name: is_leading_steed
 * Description:   Is shadow_who leading one or more steeds?
 * Returns:       int 1
 */
public int
is_leading_steed()
{
    return 1;
}

// --- Move functions ------------------------------------------------

/* Function name: st_check_follower
 * Description:   Check that the follower is where the rider is.
 * Arguments:     ob - The follower object to check.
 * Returns:       Result of check. 1/0.
 */
nomask int
st_check_follower(object follower)
{
    if (!objectp(follower) || !objectp(shadow_who))
        return 0;

    return (environment(follower) == environment(shadow_who) && shadow_who->check_seen(follower));
}

/* Function name: st_check_follower_left_behind
 * Description:   Check if the follower is left behind.
 * Arguments:     steed - The follower object to check.
 * Returns:       Result of check. 1/0.
 */
nomask int
st_check_follower_left_behind(object follower)
{
    return (environment(follower) != environment(shadow_who));
}

/* Function name: st_move_follower
 * Description:   Move the following steeds
 * Arguments:     ob - A follower to move.
 *                com - The command the leader gave
 * Returns:       Success of move.
 */
nomask int
st_move_follower(object follower, string com)
{
    int move_result;
    if (!in_move)
    {
        return 0;
    }

    move_result = (int) follower->command("$" + com);
    return move_result;
}

/* Function name: set_steed_with_auto_mount
 * Description:   set the steed with auto_mount on.
 *                This is checked each time the player moves. 
 */
public void set_steed_with_auto_mount(object o)
{
    steed_with_auto_mount = o;
}

/* Function name: move_living
 * Description:   Shadow the rider's move_living function in order to 
 *   co-move the following steeds.
 *   Functions moves the leader, then the steeds.
 *   When you want to call the original move_living 
 *   without bothering about the steed, call move_living_old in the player. 
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int    r, n;
    string vb, com;
    object env, *followers;

    env = environment(shadow_who);
    vb = query_verb();

    if (steeds)
    {
        followers = filter(steeds, st_check_follower);
    }

    // Move the shadow_who
    r = shadow_who->move_living(how, to_dest, dont_follow, no_glance);

    // If shadow_who is moved OK, move the steeds as well
    if ((!r) && (how != "X") && (!dont_follow))
    {
        // Command for the followers if this is a leader
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

        in_move = how;
        if (sizeof(followers))
        {
            map(followers, &st_move_follower(, com));
        }
    }

    in_move = 0;

    // Remove followers that didn't follow.
    if ((steeds) && (sizeof(steeds)))
    {
        int i = sizeof(steeds);
        while (i--)
        {
            if (st_check_follower_left_behind(steeds[i])) 
            {
                int sts = steeds[i]->do_unlead(shadow_who, 1);
                // Because leader has already in another room, don't tell
                // the leader he is unleading the horse.
                // follower->handle_unlead_status(sts, shadow_who);
            }
        }
    }
    
    // Check if auto_mount is on.
    if (objectp(steed_with_auto_mount))
    {
        if (
            STEED_STS_SUCCESS(
                steed_with_auto_mount->check_mounted_destination(to_dest))
            )
        {
            return steed_with_auto_mount->unlead_and_mount(r);
            // Nothing will be execute after here because shadow is removed.
        }
    }
    
    return r;
}

/* Function name: move_living_old
 * Description:   Calls original move_living function.
 * Arguments:     see move_living
 * Returns:       see move_living
 */
public varargs int
move_living_old(string how, mixed to_dest, int dont_follow, int no_glance)
{
    return shadow_who->move_living(how, to_dest, dont_follow, no_glance);
}

// Tell the steeds that their leader is not their leader anymore
// before the shadow is removed.
// remove_shadow is private to prevent malicious buggy code from
// removing this shadow.
private void
remove_shadow()
{
    if (steeds)
    {
        int i = sizeof(steeds);
        while (i--)
        {
            steeds[i]->do_unlead(shadow_who);
            steeds[i]->handle_unlead_status(STEED_STS_OK, shadow_who);
        }
    }
    ::remove_shadow();  
}

/* Function name: remove_leader_shadow
 * Description:   Call this function to remove this shadow.
 */
public void
remove_leader_shadow()
{
    remove_shadow();
}
