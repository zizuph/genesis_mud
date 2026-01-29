/*
 * A follow shadow
 *
 * Activate it with a call to the function 'follow'
 */

inherit "/std/shadow";

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

    if (!(cmd = environment(gWho)->query_dircmd()))
      cmd = query_verb();
    else
      cmd = query_verb() + " " + cmd;

    flag = gWho->move_living(how, to_dest, dont_follow, no_glance);

    if (gFollow_stop)
    {
        remove_shadow();
        return 0;
    }

    gFollow_stop = 1;

    if (!gFollower)
    {
        remove_shadow();
        return flag;
    }

    gFollower->command("$" + cmd);

    gFollow_stop = 0;
    if (!present(gFollower, environment(gWho)))
      remove_shadow();

    return flag;
}




