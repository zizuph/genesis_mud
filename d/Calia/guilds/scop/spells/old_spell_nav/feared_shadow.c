/*
 * Turn undead shadow Vekpos (turn undead) spell for the
 * Spirit Circle of Psuchae.
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

object fear_target;

void
remove_shadow()
{	
    destruct();
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


void 
enter_env(object dest, object old)
{
    shadow_who->enter_env(dest, old);
    
    if (objectp(present(fear_target, dest)) && CAN_SEE(fear_target, shadow_who))
    {
        set_alarm(0.1, 0.0, &do_run());
    }
}    