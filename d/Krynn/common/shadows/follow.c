/*
 * A follow shadow
 *
 * Activate it with a call to the function 'follow'
 */

inherit "/std/shadow";

object *followers = ({ });

public int
follow(object who, object follower)
{
    followers += ({ follower });
    return shadow_me(who);
}

void
add_follower(object who)
{
    followers += ({ who });
}

void
remove_follower(object who)
{
    followers -= ({ who, 0 });

    if (!sizeof(followers))
        remove_shadow();
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    string cmd;
    int flag;
    object *obs;
    
    obs = followers & all_inventory(environment(shadow_who));
    flag = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
    
    if (!(cmd = environment(shadow_who)->query_dircmd()))
        cmd = query_verb();
    else
        cmd = query_verb() + " " + cmd;
    
    obs->follow_object(shadow_who, cmd, to_dest);
    
    return flag;
}

int
query_follow_shadow()
{
    return 1;
}


