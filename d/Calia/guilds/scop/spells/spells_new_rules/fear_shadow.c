/*
 * Turn undead shadow Vekpos (turn undead) spell for the
 * Spirit Circle of Psuchae.
 *
 * The spell object in the target's inventory starts the
 * shadow and removes it when the time comes.
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

object feared, vekpos_obj;

void
remove_shadow()
{	
    destruct();
}

void
fear_run_away(object ob)
{
    string exit, *exits;
    
    exits = environment(shadow_who)->query_exit_cmds();

    if (!sizeof(exits))
    {
        shadow_who->catch_tell("You try to run away in fear of " +
                               ob->query_the_name(shadow_who) +
                               ", but find no place to run!");
        ob->catch_tell(shadow_who->query_The_name(ob) + 
                       " looks deathly afraid of you, but finds " +
                       "nowhere to run.\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who) +
                  " looks deathly afraid of " + QTNAME(ob) + 
                  ", but finds nowhere to run.\n", (({ob, shadow_who})));
        return;
    }

    if (!objectp(feared))
    {
        feared = ob;
    }
    
    shadow_who->catch_tell("You run away in terror from " + 
                           ob->query_the_name(shadow_who) + "!\n");
    ob->catch_tell(shadow_who->query_The_name(ob) + " looks " +
                   "at you in terror, and runs away!\n");
    tell_room(environment(shadow_who), QCTNAME(shadow_who) +
              " looks at " + QTNAME(ob) + " in terror, and " +
              "runs away!\n", (({ob, shadow_who})));

    exit = exits[random(sizeof(exits))];
    
    shadow_who->command(exit);
}

void
do_run()
{
    if (objectp(present(feared, environment(shadow_who))))
    {
        fear_run_away(feared);
    }
}

void 
enter_env(object dest, object old)
{
    int success;
    object SW = shadow_who;

    SW->enter_env(dest, old);
    
    success = (feared->resolve_task(TASK_DIFFICULT,
                                   ({SKILL_WEIGHT, 20,
                                   (feared->query_alignment())/12,
                                    SKILL_WEIGHT, 40, TS_WIS,
                                    SKILL_WEIGHT, 40, TS_OCC,
                                    SKILL_AVG, SS_SPELLCRAFT,
                                    SS_ELEMENT_LIFE, SKILL_END}),
                                    SW, 
                                   ({SKILL_AVG, SS_ELEMENT_DEATH,
                                    SW->query_prop(LIVE_I_UNDEAD),
                                    SKILL_END, SKILL_AVG, TS_INT,
                                   (SW->query_alignment())/12,
                                    SKILL_END})));
    
    if (objectp(present(feared, dest)) &&
        CAN_SEE(SW, feared) && success >=0)
    {
        
        set_alarm(0.1, 0.0, &do_run());
    }
}            

void
set_vekpos_ob(object ob)
{
  vekpos_obj = ob;
}

public void
do_die(object killer)
{
    vekpos_obj->dispel_spell_effect(killer);
    shadow_who->do_die(killer);
}
