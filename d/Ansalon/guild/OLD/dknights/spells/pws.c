/* 
 * Power Word Stun 
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
pws_target(object caster, string str) 
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
resolve_spell(object caster, object *targets, int *resist, int result) 
{ 
    object tar = targets[0]; 
    object ob; 
    
    caster->catch_tell("You utter the word: 'Lushelor'" + 
        "and points at " + tar->query_the_name(caster) + ".\n" +
        " "+ tar->query_The_name(caster) + " is instantly paralyzed "+
        "by the ancient arcane word.\n"); 

    tar->catch_tell("As "+QTNAME(caster) + " utters the word: " + 
        "'Lushelor', you instantly become paralyzed by the ancient "+ 
        "arcane word.\n"); 

    all_msg("As " + QTNAME(caster) + " utters the word: 'Lushelor', " + 
        tar->query_the_name(caster) + " instantly becomes paralyzed by the ancient "+ 
        "arcane word.\n", caster, tar); 

    setuid(); 
    seteuid(getuid()); 
    ob = make_spell_effect_object(STUN_OBJ, caster, tar, resist, result); 
    ob->move(tar,1); 
} 

public int 
pws_resist(object target) 
{ 
    int i; 
    i = target->query_magic_res(MAGIC_I_RES_MAGIC) + 
        target->query_magic_res(MAGIC_I_RES_DEATH); 
    return (i > 100 ? 100 : i); 
} 

/* 
 * Function name: config_spell 
 * Description:   configure the spell 
 * Arguments:     object caster   - the caster 
 *                object *targets - array of spell targets found 
 *                string argument - arguments to the spell invocation 
 * Returns:       1/0 - spell configured/not configured (cannot be cast) 
 */ 
public varargs int 
config_spell(object caster, object *targets, string argument) 
{ 
//    set_spell_name("Lushelor"); 
    set_spell_name("pws"); 
    set_spell_desc("Utter a word of power that stuns a single target"); 
    set_spell_element(SS_ELEMENT_DEATH, 50);
    set_spell_time(5); 
    set_spell_mana(100); 
    set_spell_offensive(1);
    set_spell_vocal(1);
    set_spell_task(TASK_DIFFICULT); 
    set_spell_target(pws_target); 
    set_spell_resist(pws_resist); 

    return 0; 
} 
