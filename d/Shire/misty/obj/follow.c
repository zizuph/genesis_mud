/*
 * A follow shadow
 *
 * Activate it with a call to the function 'follow'
 */

inherit "/std/shadow";

#define DEBUG_WHO  find_player("igneous")

#ifdef DEBUG_WHO
#define DEBUG(x)  DEBUG_WHO->catch_tell(x + "\n")
#else
#define DEBUG(x)
#endif

// Prototypes
void move_follower(string cmd);
object gWho, gFollower;
int gFollow_stop;

public void
follow(object who, object follower)
{
    gWho = who;
    gFollower = follower;

    shadow_me(gWho);
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    string cmd;
    int flag;
    if (!objectp(gFollower))
    {
	set_alarm(0.0,0.0,remove_shadow);
	return gWho->move_living(how, to_dest, dont_follow, no_glance);   
    }        
    if (!present(gFollower, environment(gWho)))
	return gWho->move_living(how, to_dest, dont_follow, no_glance);   

    flag = gWho->move_living(how, to_dest, dont_follow, no_glance);

    cmd = query_verb();
    if (cmd == "push" || cmd == "pull")
    {
	if (environment(gFollower)->item_id("door"))
	    cmd += " door";
	else
	    cmd += " wall";
	if (cmd == "push wall")
	    gFollower->hook_pushed_wall();
    } 
    set_alarm(0.2,0.0, &move_follower(cmd));
    return flag;
}

void
move_follower(string cmd)
{
    if (!objectp(gFollower))
	return;

    gFollower->command("$" + cmd);
}
