/*
 * Tracks and decays the count of kills.
 * 
 * Avoids using a prop to prevent relying on armageddon / logout 
 * - Cotillion
 */ 
inherit "/std/object";

#include <macros.h>

#include "../defs.h"

int kills;
int decay_time;

#define DECAY_GRACE_TIME         (3600*2) /* No decay until after this downtime */
#define INTERVAL_BETWEEN_DECAY   (60 * 30) /* Seconds for a decay */

void
create_object()
{
    set_name(GKEEP_KILL_TRACKER);
    set_no_show();

    add_prop(OBJ_I_NO_DROP, 1);
}

void
cleanup()
{
    if (!kills) {
        remove_object();
    }
}

void
add_kill(int count = 1)
{
    kills += count;
    decay_time = time() + DECAY_GRACE_TIME;
}

int
query_kills()
{
    int decays = (time() - decay_time) / INTERVAL_BETWEEN_DECAY;

    if (decays > 0) {
        kills = max(kills - decays, 0);
        decay_time = time();

        if (!kills) {
            set_alarm(1.0, 0.0, &cleanup());
        }
    }
    return kills;
}

int
query_level2_access() 
{
    return query_kills() >= GKEEP_KILLS_LEVEL2;
}

string
query_auto_load() 
{
    if (kills > 0) 
        return MASTER + ":" + val2str(m_save_object());
    return 0;
}

void
init_arg(string arg)
{
    m_restore_object(str2val(arg));
}

string
stat_object()
{
    string str = ::stat_object();

    str += sprintf("\nKills: %3d   Last Decay: %s\nLevel 2 access: %s\n",
            query_kills(), ctime(decay_time), query_level2_access() ? "Yes" : "No");
    return str;
}

