/************************************************

  sceduler.c - controlled simple interval timer
               by Gresolle 1993

*************************************************

  Functions:

     create_sceduler : standard create function

     query_rem_time  : returns the time remaining
                       until removal

     enable_random   : if arg to this funct <> 0 then
                       the call_outs will be randomized
		       much like /std/poison_effect

     remove_function : this function is called when the timer is
                       removed. replace it with your own msgs etc

     sceduled_function : the function to be interval-timed

     set_duration    : set the duration of the timer

     set_m_time      : set time between call_outs. if not random
                       this time will be used without modification
                       else it is used as mean time of call outs

******************************************************************/

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

int mean_time, duration, ran, remid, scedid;
object tp;

public nomask void tabort();
public nomask void sced_funct();

/* Function : enable_random
 * Descript : 1 enables random times
 */
public void
enable_random(int flag)
{
    ran = flag;
}

/* Function : query_rem_time
 * Descript : returns remaining time of sceduler effects
 */
public int
query_rem_time()
{
    return ftoi(get_alarm(remid)[2]);
}

/* Function : set_m_time
 * Descript : set mean time of call_outs
 * In       : mean time of call_outs
 */
public void
set_m_time(int mtime)
{
    mean_time = mtime;
}

/* Function : set_duration
 * Descript : set duration of sceduler
 * In       : the desired duration
 */
public void
set_duration(int dur)
{
    duration = dur;
}

/* Function : create_sceduler
 * Descript : standard create
 */
public void create_sceduler(){}

/* Function : create_object
 * Descript : set up defaults, start call_outs...
 */
public nomask void 
create_object()
{
    if (!IS_CLONE)
        return;
    tp = this_player();

    create_sceduler();
}

void
init_sceduling()
{
    remid = set_alarm(itof(duration), 0.0, &tabort());

    scedid = set_alarm(itof(mean_time), 0.0, &sced_funct());
}

/* Function : sceduled_function()
 * Descript : function called in intervals
 */
public void
sceduled_function(){}

/* Function : sced_funct
 * Descript : call the interval timed function
 */
public nomask void
sced_funct()
{
    set_this_player(tp);

    sceduled_function();
  
    if (ran)
        scedid = set_alarm(itof(mean_time / 2 + random(mean_time)), 0.0,
                           &sced_funct());
    else
        scedid = set_alarm(itof(mean_time), 0.0, &sced_funct());
}

/* Function : remove_function
 * Descript : do something when the sceduler disappears
 */
public void
remove_function(){}

/* Function : tabort
 * Descript : remove the call_outs & the object
 */
public nomask void
tabort()
{
    remove_alarm(scedid);

    set_this_player(tp);

    remove_function();

    remove_object();
}
