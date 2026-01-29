/*
 * A follow shadow
 *
 * Activate it with a call to the function 'follow'
 *
 * Taken from /d/Shire/moria/follow.c Thanks Jaypeg!
 * Tomas  -- June, 2000
 */

#include "/d/Shire/common/defs.h"

//  The number of rooms will hunt after its victim.
#define MAX_TIMES   2 + random(8)

inherit "/std/shadow";

// Prototypes
void remove_following_shadow();

object gFollower;
int gFollow_stop, gFollow_times = 0;

public void
follow(object who, object follower)
{
    gFollower = follower;
    shadow_me(who);
}

void
remove_follow_shadow()
{
    remove_shadow();
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    string cmd;
    int flag;
    int is_seen;

    cmd = query_verb();
    is_seen = CAN_SEE(gFollower,shadow_who);

    flag = shadow_who->move_living(how, to_dest, dont_follow, no_glance);

    if (gFollow_stop)
    {
        remove_following_shadow();
        return flag;
    }


    if (!gFollower)
    {
        remove_following_shadow();
        return flag;
    }

    if (is_seen)
    {
        if (!gFollow_times)
        {

        }
        gFollower->command("$" + cmd);
    }

    if (!present(gFollower, environment(shadow_who)))
    {
        remove_following_shadow();
    }

    gFollow_times++;
    if (gFollow_times == MAX_TIMES)
        gFollow_stop = 1;

    return flag;
}

void
remove_following_shadow()
{
    set_alarm(0.0,0.0,&remove_shadow());
}

void
remove_shadow()
{
    if (gFollower)
        gFollower->notify_stopped_hunt();
    destruct();
}

public void
do_die(object killer)
{

    shadow_who->do_die(killer);
    remove_following_shadow();
}

string
query_follow_times()
{
}
