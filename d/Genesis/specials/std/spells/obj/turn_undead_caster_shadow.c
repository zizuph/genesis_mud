/*
 * Turn undead shadow.
 *
 * This shadow is set up in the caster, so the spell target
 * will run when entering his presence.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include <living_desc.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>

object fear_target;
int guild_type = TS_OCC;

int
query_feared_turn_undead_shadow()
{
  return 1;
}

public void
remove_turn_undead_caster_shadow()
{
    remove_shadow();
}

void
set_fear_target(object ob)
{
    fear_target = ob;
}

void
do_run()
{
    if (objectp(present(fear_target, environment(shadow_who))))
    {
        fear_target->fear_run_away(shadow_who);
    }
}

public void
set_guild_type(int ts_guild)
{
    // Depending on the guild using this spell, set this
    // to TS_OCC, TS_LAYMAN, TS_RACE (from /sys/tasks.h)
    // for determining guild stat success.

    guild_type = ts_guild;
}

void 
enter_env(object dest, object old)
{
    int success;
    object SW = shadow_who;

    SW->enter_env(dest, old);    

    success = (SW->resolve_task(TASK_ROUTINE,
             ({SKILL_WEIGHT, 20, (SW->query_alignment())/12,
               SKILL_WEIGHT, 40, TS_WIS,
               SKILL_WEIGHT, 40, guild_type,
               SKILL_AVG, SS_SPELLCRAFT, SS_ELEMENT_LIFE, SKILL_END}),
             fear_target, 
             ({SKILL_AVG, SS_ELEMENT_DEATH, 
               fear_target->query_prop(LIVE_I_UNDEAD),
               SKILL_END, SKILL_AVG, TS_INT,
             (fear_target->query_alignment())/12, SKILL_END})));

    if (objectp(present(fear_target, dest)) &&
        CAN_SEE(fear_target, SW) && success >=0)
    {
        set_alarm(0.1, 0.0, &do_run());
    }
}    