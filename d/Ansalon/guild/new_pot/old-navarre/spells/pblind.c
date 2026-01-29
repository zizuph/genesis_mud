/*
 * This is the blind spell for the Priests of Takhisis.
 * 
 * Created by Navarre, May 2013.
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/blind";

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include <ss_types.h>
#include "../defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/std/generic_functions.c"



// Prototypes
public void     resolve_blind_spell(object caster, mixed * targets, int * resist, int result);
public string*  query_blind_ingredients(object caster);
public void     resolve_spell_resisted(object caster, object target, int resist, int result);
public void     hook_describe_blind(object caster, mixed * targets, int result);

/*
 * Function:    config_blind_spell
 * Description: Config function for blind spells. Redefine this in your
 *              own blind spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_blind_spell()
{
    set_spell_name("pblind");
    set_spell_desc("Blind someone (enemy) temporarily");
    set_spell_task(TASK_ROUTINE);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_ENCHANTMENT, 45);
    
    // Set the effect object filename
    set_spell_object(POT_SPELL_OBJS + "pblind_obj");
}


/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_tell("You throw up your hands and a stream of black " +
                       "fire flows from your fingers towards " +
                       target->query_the_name(caster) + 
                       "'s eyes. As the stream touches " + HIS(target) +
                       " eyes, it dissolves.\n");

    my_tell_roombb(environment(caster), QCTNAME(caster) + " throws up " +
                   HIS(caster) + " hands and a stream of black fire " +
                   "flows from " + HIS(caster) + " fingers towards " +
                   QTNAME(target) + "'s eyes. As the stream touches " +
                   HIS(target) + " eyes, it dissolves.\n", caster,
                   ({target}));

    if (caster->check_seen(target))
    {
        target->catch_tell(caster->query_The_name(target) + " throws " +
                           "up " + HIS(caster) + " hands and a stream " +
                           "of black fire flows from " + HIS(caster) +
                           " fingers towards your eyes. As the stream " +
                           "touches your eyes, it dissolves and you " +
                           "are left unaffected.\n");
            
        // If we attempted to blind an npc, make him attack us.           
        if (target->query_npc() && !target->query_attack())
        {
            target->command("$kill " + OB_NAME(caster));
        }
    }
    else if (target->can_see_in_room())
    {
        target->catch_tell("For a brief moment you see only black fire.\n");
    }
}
 
// HOOKS TO BE DEFINED

public void
hook_describe_blind(object caster, mixed* targets, int result)
{
    // Note sizeof(0) is 0.
    int number_of_targets = sizeof(targets);
    if (number_of_targets < 1)
    {
        return;
    }
     
    // This should not happen, but we check just in case.
    if (number_of_targets > 1)
    {
        caster->catch_tell("Error: Please report that pblind could " +
                           "target more than one living.\n");
        return;
    }

    // We now know that there is only one target.
    object target = targets[0];
    
    caster->catch_tell("You throw up your hands and a stream of black " +
                       "fire flows from your fingers towards " +
                        target->query_the_name(caster) +
                        "'s eyes. The fire enters " + HIS(target) +
                        " eyes, blinding " + HIM(target) + ".\n");

    my_tell_roombb(environment(caster), QCTNAME(caster) + " throws up " +
                   HIS(caster) + " hands and a stream of black fire flows " +
                   "from " + HIS(caster) + " fingers towards " +
                   QTNAME(target) + "'s eyes.\n", caster, ({target}));

    if (caster->check_seen(target))
    {
        target->catch_tell(caster->query_The_name(target) + " throws up " +
                           HIS(caster) + " hands and a stream of black " +
                           "fire flows from " + HIS(caster) + " fingers " +
                           "towards your eyes. The fire enters your " +
                           "eyes and you are blinded!\n");
    }
    else
    {
        target->catch_tell("Suddenly a black fire enters your eyes and you "+
                           "are blinded!\n");
    }
}

/*
 * Function:    resolve_blind_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_blind_spell(object caster, mixed * targets, int * resist, int result)
{

}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg("But " + target->query_the_name(caster) +
                          " is already blinded!\n");
    }
}

/*
 * Function:    query_blind_ingredients
 * Description: This function defines what components are required for
 *              this blind vision spell.
 */
public string*
query_blind_ingredients(object caster)
{
    return ({"eye", "gold coin"});
}
