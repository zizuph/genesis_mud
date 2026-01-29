
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/steed/new/leader_shadow";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include "/d/Genesis/steed/new/steed.h"

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
    if ((!r) && stringp(how) && (how != "X") && (!dont_follow))
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

    // Check if auto_mount is on.
    if (objectp(steed_with_auto_mount) && (!st_check_follower_left_behind(steed_with_auto_mount)) )
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
