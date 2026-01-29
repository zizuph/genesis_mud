/*
 * A follow shadow
 *
 * Activate it with a call to the function 'follow'
 */

#include "/d/Shire/common/defs.h"

//  The number of rooms bolg will hunt after his victim.
#define MAX_TIMES   8 + random(8)
#define FOLLOW_KILLS  "/d/Shire/moria/npc/bolg_hunt.log"

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
	gFollower->command("$yawn");
	gFollower->command("shout I shall kill you another day "+
	  shadow_who->query_nonmet_name()+"!");
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
	    gFollower->command("$scream");
	    gFollower->command("shout None escapes me!");
	}
	gFollower->command("$" + cmd);
    }

    if (!present(gFollower, environment(shadow_who)))
    {
	gFollower->command("scream");
	gFollower->command("shout I will find you one day "+
	  shadow_who->query_nonmet_name()+"!!!");
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
#ifdef FOLLOW_KILLS
    if (killer == gFollower)
    {
	setuid(); seteuid(getuid());
	write_file(FOLLOW_KILLS, ctime(time()) +" "+ shadow_who->query_name() +
	  " was hunted to death by "+gFollower->query_name()+".\n");
    }
#endif
    shadow_who->do_die(killer);
    remove_following_shadow();
}

string
query_follow_times()
{
    return "Bolg has followed "+shadow_who->query_name()+" "+gFollow_times +
    " times.\n";
}
