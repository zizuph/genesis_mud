/*
 * effect.c
 * 
 * This is an invisble object which makes sure that a continous effect
 * lasts for a period of time.
 *
 */

inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

int time, timeout_id;

void do_start_effect(object to) {}
void do_stop_effect(object from) {}

void
create_effect() {}

nomask void
create_object()
{
    ::create_object();

    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);

    time = 500;
    create_effect();
}


/*
 * Function name: set_time
 * Description:   This sets the length of time the effect will last,
 *		  in heartbeats
 */
void 
set_time(int t) 
{ 
    time = t; 
}


int
query_time_left()
{
   mixed *call;
   call = get_alarm(timeout_id);
   return ftoi(call[2]);
}

/*
 * Function name: query_time
 * Description:   This returns the remaining time the effect will last, 
 *                in heartbeats
 */
int 
query_time() 
{ 
    return time; 
}

/*
 * Function name: query_auto_load
 * Description:   Used to reload the effect into the player if it hasn't
 * 		  expired when he quits.  
 */
string
query_auto_load()
{
    return MASTER + ":" + query_time_left();
}

/*
 * Function name: init_arg
 * Description:   Parses the data from the saved object.
 */
void
init_arg(string arg)
{
    string *arglist;

    arglist = explode(arg,",");

    sscanf(arglist[0], "%d", time);
}

/*
 * Function name: timeout
 * Description:   This is called when the effect duration has expired.
 * 		  It simply removes itself.
 */
void
timeout()
{
    remove_object();
}

/*
 * Function name: new_timeout
 * Arguments:	  in_time : The new timeout for the effect.
 * Description:   This is called when the timeout is to be postponed
 * 		  It simply removes the callout "timeout" and calls
 *                a new "timeout" in in_time seconds.
 */
void
new_timeout(int in_time)
{
    remove_alarm(timeout_id);
    if(in_time<0)
	timeout();
    else
        timeout_id = set_alarm(itof(in_time),0.0,&timeout());
}

void
enter_env(object dest, object old)
{
    object recipant;
    ::enter_env(dest, old);

    recipant = environment(this_object());
    /* Find out who owns us */
    if (!living(recipant))
    {
         /* If they aren't living, we punt. */
         remove_object();
         return;
    }
 
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    do_start_effect(dest);
    if(time>=0)
       timeout_id = set_alarm(itof(time),0.0,&timeout());
}

void
leave_env(object from, object to)
{
    do_stop_effect(from);
    ::leave_env(from, to);
}

/*
 * Function name: stat_object
 * Description:   Called when wizard stats the object
 * Returns:	  A string describing the object.
 */
string
stat_object()
{
    string str;

    str = ::stat_object();

    str += "Time:     " + time + "\n";

    return str;
}

