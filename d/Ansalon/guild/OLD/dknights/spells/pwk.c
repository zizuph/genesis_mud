/* 
 * Power Word Kill 
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
pwk_target(object caster, string str) 
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
    int damage; 

    object tar = targets[0]; 

//  Check to make sure the target is still present, otherwise 
//  skip that particular target. 
    if (environment(tar) != environment(caster)) 
    { 
        caster->catch_tell("Your target is no longer present.\n"); 
        return; 
    } 
    else 
    { 
        damage = random(1000) + 750;

//      The resist array is filled with each target's resistance 
//      to death. The greater resistance to death, the less 
//      chance they are damaged. 
//      The target resisted the spell. Only give him half damage.
        if (resist[0] > random(100)) 
            damage = damage / 2;

        caster->catch_tell("You utter the word: 'Shi'el'" + 
            "and points at " + tar->query_the_name(caster) + ". " + 
            tar->query_The_name(caster) + " screams in agony as "+
            HE(tar)+ " hears the ancient "+ "arcane word.\n"); 

        tar->catch_tell("As " + QTNAME(caster) + " utters the word: " + 
            "'Shi'el'.  You scream in agony as you hear the ancient "+ 
            "arcane word.\n"); 

        all_msg("As " + QTNAME(caster) + " utters the word: 'Shi'el' " + 
            "and points at " + tar->query_the_name(caster) + ". " + 
            tar->query_The_name(caster) + " screams in agony as "+
            HE(tar)+ " hears the ancient arcane word.\n", caster, tar); 

        // Hit the player with the spell and start the fight.
        tar->heal_hp(-damage);
        tar->start_fight(caster); 
    } 
} 

public int 
pwk_resist(object target) 
{ 
    int i; 
    i = target->query_magic_res(MAGIC_I_RES_MAGIC) + 
        target->query_magic_res(MAGIC_I_RES_DEATH); 
    return (i > 100 ? 100 : i); 
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
    set_spell_name("Shiel"); 
    set_spell_name("pwk");
    set_spell_desc("Utter a word of Power that damages a single target"); 
    set_spell_element(SS_ELEMENT_DEATH, 50); 
    set_spell_time(5); 
    set_spell_mana(700); 
    set_spell_offensive(1);
    set_spell_vocal(1);
    set_spell_task(TASK_DIFFICULT); 
    set_spell_target(pwk_target); 
    set_spell_resist(pwk_resist); 
} 
