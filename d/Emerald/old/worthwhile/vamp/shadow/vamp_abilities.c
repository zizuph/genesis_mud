/*
 * Some routines generally related to using vampire abilities
 */

#include "/d/Emerald/sys/skills.h"
#include <tasks.h>

#define SW shadow_who
#define ALARM_INTERVAL 60.0

#define POWER_CHECK_LOG(s) \
    setuid(); seteuid(getuid()); \
    write_file(VAMP_LOG_DIR + "power_check", s + "\n");
#undef POWER_CHECK_LOG

static private int cost_alarm_id;
static private int mana_per_interval;

/* 
 * Function name: power_check
 * Description:   Check to see if a vampire is able to perform
 *                a vampire ability of a given level.
 * Arguments:     int level - the level of the ability.
 * Returns:       as resolve_task() in /std/living.c
 */
int
power_check(int level)
{
    int stat, diff, success;
  
    stat = query_effective_vamp_stat();
    diff = TASK_ROUTINE + max(-100, (level - stat) * 80);

    success = SW->resolve_task(MAX(0, diff),
	({ query_effective_vamp_stat, SS_VAMP_FOCUS }));
    
#ifdef POWER_CHECK_LOG
    POWER_CHECK_LOG(capitalize(SW->query_real_name()) + " base: " +
        query_base_vamp_stat() + " eff: " + stat + " level: " + level +
        " task: " + diff + " suc: " + success);
#endif

   return success;
}

void
apply_costs()
{
    if (SW->query_linkdead() &&
        ((time() - SW->query_linkdead()) > (60 * 15)))
    {
        return;
    }

    if (mana_per_interval)
    {
        SW->add_mana(-mana_per_interval);

        if (SW->query_mana() <= 1)
	{
            SW->catch_tell("Mentally exhausted, your abilities fail you.\n");
            //set_unseen(0);
	}
    }
}

int
query_mana_drain()
{
    return mana_per_interval;
}

void
add_mana_drain(int amnt)
{
    mana_per_interval += amnt;

    if (mana_per_interval && !cost_alarm_id)
    {
        cost_alarm_id = set_alarm(ALARM_INTERVAL, ALARM_INTERVAL, apply_costs);
    }
    else if (!mana_per_interval && cost_alarm_id)
    {
        remove_alarm(cost_alarm_id);
        cost_alarm_id = 0;
    }
}

/*
 * Function name: cmdhooks_break_spell
 * Description:   This is normally called from the combat system
 *                to break a spell on which the player is concentrating.
 *                We use it to cut off any vamp abilities which should
 *                be interrupted for similar reasons.
 * Arguments:     as for cmdhooks_break_spell on /std/living.c
 * Returns:       as for cmdhooks_break_spell on /std/living.c
 */
int cmdhooks_break_spell(string msg)
{
    int res = SW->cmdhooks_break_spell(msg);
  
#ifdef VAMP_ABILITIES
    VAMP_ABILITIES->break_command(SW);
#endif

    break_vamp_drain();
  
    return res;
}
