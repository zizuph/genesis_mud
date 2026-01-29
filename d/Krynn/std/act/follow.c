/*
 * This is basically overriding the follow functions in /std/act/domove.c
 * 
 * This is because those suck.
 * When they stop sucking remove this.
 */
static float follow_time = 2.0;
static object follow_ob;
static int follow_alarm;

/*
 * Function Name: set_follow
 * Description  : Sets the living this monster should follow.
 * Arguments    : ob - the object we want to follow
 */
void
set_follow(object ob)
{
    object shad;

    follow_ob = ob;

    if (!follow_ob->query_follow_shadow())
    {
        shad = clone_object("/d/Krynn/common/shadows/follow");
        if (!shad->shadow_me(follow_ob))
        {
            shad->remove_object();
            return;
        }
    }
    
    follow_ob->add_follower(this_object());    
}

/*
 * Function Name: query_follow
 * Description  : Returns the object we are follinwg if we are
 *                following anyone.
 * Returns      : object - the followed
 */
object
query_follow()
{
    return follow_ob;
}

/*
 * Function Name: stop_follow
 * Description  : Makes us stop following whoever we is following
 */
void
stop_follow()
{
    follow_ob->remove_follower(this_object());
    follow_ob = 0;
}

void
follow_cmd(object who, string cmd)
{
    if (!objectp(who) || !stringp(cmd) || (environment(who) == environment()))
        return; 
        
    command(cmd);
}

/*
 * Function Name: follow_object
 * Description  : This is called from the follow shadow to notify
 *                that the one we are following moved.
 * Arguments    : object - the one we are follinwg
 *                string - the cmd we could use to follow him
 *                mixed  - the destination it moved to
 */
void
follow_object(object who, string cmd, mixed to_dest) {
    string dest;
    string *restrain;
    int size;

    if (stringp(to_dest))
        dest = to_dest;

    if (objectp(to_dest))
        dest = file_name(to_dest);
    
    if (!stringp(dest) || !stringp(cmd))
        return;
    
    /* By default we don't follow outside the restrain path if one is set */
    restrain = this_object()->query_restrain_path();
    if (pointerp(restrain) && sizeof(restrain) &&
        !sizeof(filter(restrain,  &wildmatch(, dest) @ &operator(+)(, "*"))))
    {
        /* No restrain path matched */
        return;
    }
    
    if (get_alarm(follow_alarm))
        remove_alarm(follow_alarm);
    
    follow_alarm = set_alarm(rnd() * follow_time, 0.0, &follow_cmd(who, cmd));
}

/*
 * Function Name: set_follow_time
 * Description  : Sets the delay before we follow someone.
 *                In reality the delay is time * rnd()
 * Arguments    : float - the time
 */
void
set_follow_time(float f)
{
    follow_time = f;
}

/*
 * Function Name: query_follow_time
 * Description  : Returns the time we wait until we run after the 
 *                one we are follinw.g
 * Returns      : float - the time
 */

float
query_follow_time()
{
    return follow_time;
}
