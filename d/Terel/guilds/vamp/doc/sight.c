/*
 *
 *  Sight
 *
 *  For spell effect description, see doc/sight.txt
 *
 *  Created May 2008, by Novo
 *  Modifications:
 *   1  Dec 2008: Lilith
 *    shortened cast time to 2 seconds, updated duration to 30 minutes instead of 50,
 *    updated mana cost to 91 from 53 to pay for shorter cast time, lowered blood
 *    cost since spell will have to be cast twice as often.
 */

#include "../guild.h";

inherit SPELL_DIR+"blood_spell";

#include <stdproperties.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>

public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (::config_spell(caster,targets,argument))
        return 1;
        
    set_spell_name("sight");
    set_spell_mana(91);
    set_spell_time(2);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_DIVINATION, 30);

    set_blood_cost(4);
    set_min_guild_stat(0);
    
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_vocal(1);
    set_spell_visual(0);
    
    set_spell_target(target_one_present_living);

    set_spell_desc("Improve your clarity of vision");
    
    set_spell_object(SPELLOBJ_DIR+"sight_obj");
    return 0;
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (result>0)
    {
        //We borrow upon the bloodguards mana and blood, if we can.
        if (caster!=targets[0])
        {
            int mana_pay=min(targets[0]->query_mana(),
                get_spell_mana());
            int blood_pay=min(targets[0]->query_blood(),
                query_blood_cost());
            if (mana_pay>0)
            {
                caster->add_mana(mana_pay);
                targets[0]->add_mana(-mana_pay);
            }
            if (blood_pay>0)
            {
                caster->add_blood(blood_pay);
                targets[0]->add_blood(-blood_pay);
            }
        }
        make_spell_effect_object(query_spell_object(), caster, 
            targets,resist,result);
    }
    else
    {
        write(query_ability_fail());
    }

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
    if (actor!=targets[0] && !IS_BG(targets[0]))
    {
        actor->catch_msg("You cannot share you gift of sight with "+
        QTNAME(targets[0])+".\n");
        return 0;
    }
    if (present("_sight_obj",targets[0]))
    {
        actor->catch_msg(
        (actor==targets[0] ? "Your" : CAP(POSS(targets[0]))) +
            " vision is already enhanced. If you want to stop "+
            "it and re-cast, do <stop sight> first.\n");
        return 0;
    }
    return ::check_valid_action(actor,targets,arg,execute);
}


