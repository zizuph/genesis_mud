/*
 *
 *  Doll
 *
 *  For spell effect description, see doc/doll.txt
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

public object * target_other_vampire(object actor, string str);


public void
config_spell()
{
    ::config_spell();

    set_spell_name("doll");
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_ILLUSION, 40);
    set_blood_cost(5);
    
    set_min_guild_stat(75);
    
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_vocal(1);
    set_spell_offensive(0);
    
    set_spell_target(target_other_vampire);

    set_spell_desc("Create an image of another vampire");
    
    set_spell_object(SPELLOBJ_DIR+"doll_obj");
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
    if (objectp(actor->query_clone()))
    {
        actor->catch_msg("You find the single illusion a sufficient "+
        "mental tax to maintain.\n");
        return 0;
    }
    return ::check_valid_action(actor,targets,arg,execute);
}


public object *
target_other_vampire(object actor, string str)
{
    object *oblist;
    
    if (!strlen(str))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({ });
    }

    if (!parse_command(str, filter(all_inventory(environment(actor)), 
                            &->query_vampire()),
                            "[at] / [on] [the] %l", oblist))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 2)
    {
        actor->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }

    return oblist[1..];
}