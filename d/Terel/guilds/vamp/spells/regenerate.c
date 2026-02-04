*
 *
 *  Regenerate
 *
 *  For spell effect description, see doc/regenerate.txt
 *
 *  Created Jan 2009, by Lilith
 *   nearly identical to constrict, with opposite effect
 */

#include "../guild.h";

inherit SPELL_DIR+"blood_spell";

#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include <language.h>
#include <macros.h>
#include <formulas.h>

public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (::config_spell(caster,targets,argument))
        return 1;

    set_spell_name("regenerate");
    set_spell_mana(36);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_CONJURATION, 60);

    set_blood_cost(2);
    
    set_min_guild_stat(80);
    
    set_spell_resist(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    
    set_ability_target(target_caster);

    set_spell_desc("Heal your sounds at an accelerated rate");
    
    return 0;
}


public void special_did_heal(int hp,object target)
{
    TP->catch_msg("You focus your inner energies and your wounds "+
        "close of their own volition.\n");

    object * watchers = WATCHERS(TP) - ({ TP });
    
    watchers->catch_msg(QCTNAME(TP)+" closes "+
    POSS(enemy) + " eyes briefly as "+ POSS(TP) "+
    "injuries close before your eyes.\n");
}


public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (result==0)
    {
        write(query_ability_fail());
        return;
    }
    
    if (result>200)
        result=200;

    int pen=(caster->query_skill(SS_ELEMENT_AIR)+
    caster->query_skill(SS_FORM_CONJURATION))/2;
    
    int heal=F_PENMOD(pen,result) *
        F_STR_FACTOR((caster->query_stat(SS_INT)+
        caster->query_stat(SS_WIS))/2)/100;

    caster->heal_hp(heal);  
  
    special_did_heal(heal, caster);
    
}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int check_valid_action(object actor,mixed * targets,string arg,int
                                execute = 0)
{
    object diamond;
    if (!::check_valid_action(actor,targets,arg,execute))
    {
        return 0;
    }

    if (!(diamond=present("_swallowed_diamond",actor)))
    {
        actor->catch_tell("You do not have a focal diamond within "+
            "your body.\n");
        return 0;
    }
    if (execute)
    {
        diamond->reduce_charges();
    }
    return 1;
}
