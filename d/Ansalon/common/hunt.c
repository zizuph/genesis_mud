/*
 * NOTE: This file is to be included (not inherited)
 *
 * Hunting stuff by Milan
 * Modified 9.9.1999
 *    added check for LIVE_I_STUNNED
 *    delayed hunting by 0.2 sec.
 *                                 Milan
 */

#include <stdproperties.h>

int hunt_alarm;

void
remove_prop(string prop)
{
    if(prop != LIVE_O_ENEMY_CLING)
	::remove_prop(prop);
}

void
do_hunt_enemy(object who, string cmd)
{
    if (!stringp(cmd) || !objectp(who))
	return;
    command(cmd);
    hit_me(0, 0, who, 0);
    who->hit_me(0, 0, this_object(), 0);
    hunt_alarm = 0;
}

object
query_hunt_enemy()
{
    object who = previous_object(-1)->qme();
    string com, cmd = who->query_prop(LIVE_S_LAST_MOVE);
    string rest;

    if (hunt_alarm ||
	!who->check_seen(this_object()) ||
	this_object()->query_prop(LIVE_I_STUNNED))
	return 0;

    if (com = environment()->query_dircmd())
    {
        cmd += " " + com;
    }
    hunt_alarm = set_alarm(0.2, 0.0, &do_hunt_enemy(who, cmd));
    return 0;
}

void
set_hunt_enemy(int i = 1)
{
    if(i)
	add_prop(LIVE_O_ENEMY_CLING, query_hunt_enemy);
    else
	::remove_prop(LIVE_O_ENEMY_CLING);
}
