/* This object manages domain-wide time-dependant events
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types
#pragma no_shadow

#include "/d/Earthsea/sys/time.h"

/*
 * Function name: hourly_events
 * Description:   Calls hourly_event() in the environments of
 *                interactive players in the Earthsea domain
 *                and reschedules for next hour.
 */
nomask void
hourly_events()
{
    object *people = users(), env, *env_arr;
    int i;
    mapping env_map = ([]);
    string err;

    for (i = 0; i < sizeof(people); i++)
    {
        if (interactive(people[i]) && (env = environment(people[i])) &&
            (env->query_domain() == "Earthsea"))
	{
            // use a mapping so we don't have to worry about duplicates
            env_map[env] = 1;
	}
    }

    setuid();
    seteuid(getuid());

    env_arr = m_indices(env_map);
    for (i = 0; i < sizeof(env_arr); i++)
    {
        if (strlen(err = catch(env_arr[i]->hourly_event())))
        {
            log_file("scheduler_err", "- " + ctime(time()) + " " + 
                file_name(env_arr[i]) + ": " + err);
        }
    }

    SCHEDULE_EVENT(this_object(), hourly_events, -1, -1, -1, -1, 0);
}

/*
 * Function name: create
 * Description:   schedule next hour's event at startup
 */
static nomask void
create()
{
    setuid();
    seteuid(getuid());
    SCHEDULE_EVENT(this_object(), hourly_events, -1, -1, -1, -1, 0);
}
