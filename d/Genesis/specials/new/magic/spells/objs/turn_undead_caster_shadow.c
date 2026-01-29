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
int alarm_track;

#define TURN_SPELL "/d/Genesis/specials/new/magic/spells/unfinished/turn_undead"

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

    alarm_track = 0;
}

void 
enter_env(object dest, object old)
{
    int success;
    object SW = shadow_who;

    SW->enter_env(dest, old);    

    function ability_hit_function = TURN_SPELL->query_ability_hit_function();
    success = ability_hit_function(fear_target, SW, ({ 0 }) );

    if (objectp(present(fear_target, dest)) &&
        CAN_SEE(fear_target, SW) && success >=0)
    {
        if(!alarm_track)
        {
            set_alarm(3.0, 0.0, &do_run());
            alarm_track = 1;
        }
    }
}  
  