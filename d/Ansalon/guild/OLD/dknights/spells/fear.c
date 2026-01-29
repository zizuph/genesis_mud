/* 
 * Cause Fear 
 */ 

#pragma strict_types 

inherit "/d/Ansalon/guild/dknights/std/std_dknight_spell"; 

#include "/d/Ansalon/common/defs.h" 
#include "../local.h" 
#include <macros.h> 
#include <tasks.h> 
#include <ss_types.h>
#include <filter_funs.h> 

public object * 
fear_target(object caster, string str) 
{ 
    if (!stringp(str) || (str == "")) 
        return spell_target_one_present_enemy(caster, str); 
    else 
        return spell_target_one_other_present_living(caster, str); 
} 

/* 
 * Function name: resolve_spell 
 * Description:   Complete the casting of the spell 
 * Arguments:     object caster   - the caster 
 *                object *targets - an array of targets 
 *                int *resist     - resistance percentages corresponding to 
 *                                  each target 
 *                int result      - how well the spell was cast 
 */ 
public void 
resolve_spell( object caster, object *targets, int *resist, int result ) 
{ 
    string *dirs;
    int i = 0; 
    int location; 

    object tar = targets[0]; 

    caster->catch_tell("You attempt to frighten "+tar->query_the_name(caster)+ ".\n"); 

//  Check to make sure the target is still present, otherwise 
//  skip that particular target. 

    if (environment(tar) != environment(caster)) 
    { 
        caster->catch_tell("Your target is no longer present.\n"); 
        return; 
    } 
    else 
    { 
//      The resist array is filled with each target's resistance 
//      to death. The greater resistance to death, the less 
//      chance they are scared. 
        if (resist[0] < random(100) || tar->query_stat(SS_DIS) / 10 < random(100) ||
            tar->query_prop("_npc_i_no_run_away")) 
        { 
//          Make it look as if the player has really left, stopping 
//          fights and sending hunting messages where appropriate. 
            dirs = E(tar)->query_exit_cmds(); 
            location = sizeof(dirs); 
            tar->command("$scream");
	    caster->tell_watcher(QCTNAME(tar) + " panics and attempts to flee.\n", tar);
            tar->catch_tell("Your legs run away with you!\n"); 
            tar->command(dirs[random(location)]); 
        } 
        else 
        { 
//          Give a message to those that resist the fear spell. 
//          The spell target will also attack the player. 
            tar->catch_tell("You are not affected by "+ 
            caster->query_The_name(tar) + "''s attempt to frighten you.\n"); 
            write(tar->query_The_name(caster)+ " doesn't seem affraid of you.\n");
            tar->start_fight(caster); 
        } 
    } 
} 

/* 
 * Function name: create_spell_pmirage 
 * Description:   configure the spell 
 * Arguments:     object caster   - the caster 
 *                object *targets - array of spell targets found 
 *                string argument - arguments to the spell invocation 
 * Returns:       0/1 - spell configured/not configured (cannot be cast) 
 */ 
public varargs int 
config_spell(object caster, object *targets, string argument) 
{ 
    set_spell_name("fear"); 
    set_spell_desc("Attempt to frighten a single target"); 
    set_spell_element(SS_ELEMENT_DEATH, 35); 
    set_spell_stationary(1); 
    set_spell_peaceful(1);
    set_spell_offensive(1);
    set_spell_vocal(0);
    set_spell_target(fear_target); 
    set_spell_time(3); 
    set_spell_mana(30); 
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist_basic); 

    return 0; 
} 
