/*
 * Turn target shadow spell.
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

object feared, turn_target_obj;
int alarm_track;

#define TURN_SPELL "/d/Genesis/specials/new/magic/spells/unfinished/turn_target"
#define DEBUG(x)   find_player("arman")->catch_msg("[turn] " + x + "\n")

public void
remove_turn_target_shadow()
{
    remove_shadow();
}

void
fear_run_away(object ob)
{
    string exit, *exits;
    
    exits = environment(shadow_who)->query_exit_cmds();


    if (!objectp(feared))
    {
        feared = ob;
    }

    function ability_hit_function = TURN_SPELL->query_ability_hit_function();
    int success = ability_hit_function(feared, shadow_who, ({ 0 }) );

    // DEBUG("Turn success check (enter_env): " +success+ ".");

    if (success < 0)
    {
        shadow_who->catch_tell("You resist the compulsion to run in fear of " +
            ob->query_the_name(shadow_who) + ".");
        ob->catch_tell(shadow_who->query_The_name(ob) + 
            " resists the compulsion to run from you.\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who) +
            " resists the compulsion to run from " + QTNAME(ob) + 
            ".\n", (({ob, shadow_who})));
        return;
    }

    if (!sizeof(exits))
    {
        shadow_who->catch_tell("You try to run away in fear of " +
            ob->query_the_name(shadow_who) + ", but find no place to run!");
        ob->catch_tell(shadow_who->query_The_name(ob) + 
            " looks deathly afraid of you, but finds nowhere to run.\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who) +
            " looks deathly afraid of " + QTNAME(ob) + 
            ", but finds nowhere to run.\n", (({ob, shadow_who})));
        return;
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

    alarm_track = 0;
}

void 
enter_env(object dest, object old)
{
    int success;
    object SW = shadow_who;

    SW->enter_env(dest, old);

    function ability_hit_function = TURN_SPELL->query_ability_hit_function();
    success = ability_hit_function(feared, shadow_who, ({ 0 }) );
    
    // DEBUG("Turn success check (enter_env): " +success+ ".");
    
    if (objectp(present(feared, dest)) &&
        CAN_SEE(SW, feared) && success >=0)
    {
        if(!alarm_track)
        {
            set_alarm(3.0, 0.0, &do_run());
            alarm_track = 1;
        }
    }
}            

void
set_turn_target_ob(object ob)
{
  turn_target_obj = ob;
}

public void
do_die(object killer)
{
    turn_target_obj->dispel_spell_effect(killer);
    shadow_who->do_die(killer);
}
