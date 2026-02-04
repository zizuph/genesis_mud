/*
 *
 *  Obfuscate
 *
 *  For spell effect description, see doc/obfuscate.txt
 *
 *  Created May 2008, by Novo
 *
 *  Modifications:
 *    May 2009 - Changed the cost for obfuscate to be incremental.
 *    October 2009 - Changed argument list for config_spell since base
 *                   spell.c was changed. - Petros
 */

#include "../defs.h";

inherit SPELL_DIR+"blood_spell";

#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>

public void
config_spell()
{
    ::config_spell();

    set_spell_name("obfuscate");
    set_spell_time(6); 
    set_spell_mana(30); // total cost 90. 30 initial, 60 incremental
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_ILLUSION, 60);

    set_blood_cost(8); // total cost 24. 8 initial, 16 incremental
    
    set_min_guild_stat(100);
    
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(0);
    set_spell_peaceful(1); // Changed February 2009
    set_spell_offensive(0);
    set_spell_vocal(0); // Changed February 2009
    
    set_spell_target(target_one_present_living);

    set_spell_desc("Mentally cloud your presence");
    
    set_spell_object(SPELLOBJ_DIR+"obfuscate_obj");
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    make_spell_effect_object(query_spell_object(), caster, 
        targets,resist,result);
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
    if (actor->query_stalk())
    {
        /*
         * Changed so that once obfuscated, you can no longer enhance
         * any more. February 2009.
         * Rationale:
         *  Obfuscate will be fixed so that it cannot be fail-proof. Currently,
         *  the spell uses a resolve_task to check on success/failure, hanging
         *  on to the result so that further testing is not necessary. However,
         *  a failure result can be removed by the simple act of recasting
         *  the spell which calls enhance_stalk_block() in the stalk.c part
         *  of the shadow. Doing this gives an essential 100% success rate,
         *  removing the purpose of the original call to resolve_task. Worse
         *  yet, the enhance_stock_block() calls continually raise the value
         *  for resolve_task, making it even less likely (impossible) to fail.
         */
        actor->catch_tell("You attempt to focus further "
            + "but find you cannot mask yourself any better.\n");
        return 0;
    }

    if (targets[0] != actor)
    {
        actor->catch_tell("You can only mask yourself from others.\n");
        return 0;
    }            

    return ::check_valid_action(actor,targets,arg,execute);
}

