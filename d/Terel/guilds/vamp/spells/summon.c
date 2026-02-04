/*
 *
 *  Summon
 *
 *  For spell effect description, see doc/summon.txt
 *
 *  Created May 2008, by Novo
 *  Modifications:
 *    October 2009 - Changed argument list for config_spell since base
 *                   spell.c was changed. - Petros
 */

#include "../defs.h";

inherit SPELL_DIR+"blood_spell";

#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

public void
config_spell()
{
    ::config_spell();
        
    set_spell_name("summon");
    set_spell_mana(28);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);

    set_blood_cost(9);
    
    set_min_guild_stat(30);
    
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_vocal(1);
    
    set_spell_target(spell_target_caster);

    set_spell_desc("Summon a messenger");
    
    set_spell_object(SPELLOBJ_DIR+"messenger");
    
    set_ability_fail("No creature heeds your summons.\n");
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
    if (environment(actor)->query_prop(ROOM_I_INSIDE))
    {
        write("You cannot summon a creature of darkness indoors.\n");
        return 0;
    }
    if (MASTER_OB(environment(actor))==ROOM_DIR+"air")
    {
        write("You cannot summon a creature of darkness while in "+
        "flight.\n");
        return 0;
    }
    return ::check_valid_action(actor,targets,arg,execute);
}

