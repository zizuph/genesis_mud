/*
 * Logs the kill of npcs. Borrowed from Shire
 * - Finwe, July 2007
 * 
 * To use this, do this:
 *      inherit KILL_LOGGER;
 *
 * When you create the npc, do this:
 *      set_kill_log_name("name defined in set_name()");
 *
 */

#include "/d/Faerun/defs.h"
#include <filter_funs.h>

static string gKiller_log_name;
static int    gKiller_log_size = 25000;

nomask public void
set_kill_log_size(int size)
{
    gKiller_log_size = size;
}

nomask public void
set_kill_log_name(string name)
{
    gKiller_log_name = name;
}

public int
second_life(object killer)
{
    object *team;
    int i, sz;
    string to_write;

    if (!objectp(killer) || !living(killer))
	    return 0;
    if (gKiller_log_name)
    {
	    FIXEUID
	    team = killer->query_team_others();
	    team = filter(team, &operator(==) (ENV(killer)) @ environment);
	    sz = sizeof(team);
	    to_write = ctime(time()) + " " + CAP(killer->query_real_name()) +
	        " ("+killer->query_average_stat()+") killed "+TO->query_name() +
	        (sizeof(team) ? " with the help of:\n" : ".");
	    for (i = 0; i < sz; i++)
	    {
	        to_write += CAP(team[i]->query_real_name())+" ("+
	            team[i]->query_average_stat()+")     ";
	    }
	    to_write += "\n";
	    log_file("kill/" + gKiller_log_name, to_write, gKiller_log_size);
	    //  Now write it to the master file.
	    log_file("kill/master_kill_log", to_write, -1);
    }
    return 0;
}
