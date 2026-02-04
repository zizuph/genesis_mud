/*
 *
 *  Dominate
 *
 *  For spell effect description, see doc/dominate.txt
 *
 *  Created May 2008, by Novo
 *
 * Modifications
 *  9/25/2009 - Fixed targeting to be able to use words like "second"
 *              (Petros)
 *  October 2009 - Changed argument list for config_spell since base
 *                 spell.c was changed. - Petros
 */

#include "../defs.h";

inherit SPELL_DIR+"blood_spell";

#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>
#include <language.h>
#include <macros.h>

#define CONTROLLED_RACES ({ "wolf", "bat", "rat" })

public object * target_npc(object actor, string str);


public void
config_spell()
{
    ::config_spell();

    set_spell_name("dominate");
    set_spell_mana(105);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 30);
    set_spell_form(SS_FORM_ILLUSION, 40);
    set_blood_cost(15);
    
    set_min_guild_stat(110);
    
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(0);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    
    set_spell_target(target_npc);

    set_spell_desc("Control the mind of another creature");
    
    set_spell_object(SPELLOBJ_DIR+"dominate_obj");
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int i=resist[0];
    if (!targets[0]->query_humanoid() && 
         member_array(targets[0]->query_race_name(),CONTROLLED_RACES)<0)
    {
        i+=20;
    }
    if (result>0 && random(100)>i)
    {
        make_spell_effect_object(query_spell_object(), caster, 
            targets,resist,result); 
    }
    else
    {
        caster->catch_msg(QCTNAME(targets[0])+" resists your attempts to "+
        "control "+ OBJ(targets[0]) + ".\n");
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
    object * dominated=actor->query_dominated();
    if (sizeof(dominated)>actor->query_vamp_stat()/50)
    {
        write("Your control over " + sizeof(dominated) + 
        (sizeof(dominated)==1 ? " mortal " : " mortals ") +
        "is the most you can manage.\n");
        return 0;
    }
    if (targets[0]->query_dominated())
    {
        actor->catch_msg(QCTNAME(targets[0]) + " is already under the " +
        "influence of domination.\n");
        return 0;
    }
    return ::check_valid_action(actor,targets,arg,execute);
}


public object *
target_npc(object actor, string str)
{
    mixed * oblist;
    
    if (!strlen(str))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({ });
    }

    object * candidates=filter(all_inventory(environment(actor)),
                    &->query_npc());
    candidates-= ({ actor });
    
    if (!parse_command(str, candidates,
                            "[at] / [on] [the] %l", oblist))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }
    
    object target;
    // targets contains an array. see man parse_command for the array
    // format. We need to determine the actual target from this array
    if (oblist[0] < 0)
    {
        // We get the index by multiplying by -1
        target = oblist[oblist[0] * -1];
    }
    else if (oblist[0] == 1)
    {
        // If it returns 1, then the first object is returned
        target = oblist[1];
    }
    else if (oblist[0] == 0 || oblist[0] > 1)
    {
        if (sizeof(oblist) > 2)
        {
            // specified more than one.
            actor->catch_tell("You can only target one at a time.\n");
            return ({ });
        }
        target = oblist[1];
    }
        
    if (!objectp(target))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }
    
    if (target->query_prop(LIVE_I_UNDEAD))
    {
        actor->catch_tell("The undead do not have the mortal instincts "+
        "that allow you to control them.\n");
        return ({ });
    }
    
    /* 
     * Removed ability to dominate messengers of any kind. February 2009.
     * Rationale:
     *  Dominate will be changed so that it cannot be used on messengers
     *  of any kind. Dominate is a very cool ability, and the idea that you
     *  can see through the eyes of a dominated valid npc is wonderful. The
     *  ability to glue a hidden camera to a postcard is not so cool.
     */
    if (target->id("messenger")
        || IN_ARRAY("/lib/messenger.c", inherit_list(target)))
    {
        actor->catch_tell("Messengers do not have the mortal instincts "
            + "that allow you to control them.\n");
        return ({ });
    }
    
    return ({ target });
}
