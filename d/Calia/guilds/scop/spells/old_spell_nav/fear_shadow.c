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

object feared;

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
            ob->query_the_name(shadow_who) + ", but find no place to run!");
        ob->catch_tell(shadow_who->query_The_name(ob) + " looks deathly" +
            " afraid of you, but finds nowhere to run.\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who) + " looks" +
            " deathly afraid of " + QTNAME(ob) + ", but finds nowhere to" +
            " run.\n", (({ob, shadow_who})));
        return;
    }

    if (!objectp(feared))
    {
        feared = ob;
    }
    
    shadow_who->catch_tell("You run away in terror from " + 
        ob->query_the_name(shadow_who) + "!\n");
    ob->catch_tell(shadow_who->query_The_name(ob) + " looks at you in" +
        " terror, and runs away!\n");
    tell_room(environment(shadow_who), QCTNAME(shadow_who) + " looks" + 
        " at " + QTNAME(ob) + " in terror, and runs away!\n", 
        (({ob, shadow_who})));

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
    shadow_who->enter_env(dest, old);
    
    if (objectp(present(feared, dest)) && CAN_SEE(shadow_who, feared) )
    {
        set_alarm(0.1, 0.0, &do_run());
    }
}            