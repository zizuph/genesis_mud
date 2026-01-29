/*
 * pTell
 * Modified to the new magic system - April 2016
 *
 * Changes:
 * Carnak - 2017-06-27: Added gmcp comms to allow for a unique message in
 *                      the gmcp list.
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/fartell";

#include "../guild.h"
#include "../spells.h"
#include "../admin/admin.h"

inherit GUILDDIRSPELL + "common";

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

#define HIS(x)        x->query_possessive()
#define HIM(x)        x->query_objective()
#define HE(x)         x->query_pronoun()


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
public int 
query_spell_level(void)
{
    return 1;
}

/*
 * Function:    config_fartell_spell
 * Description: Config function for fartell spells. Redefine this in your
 *              own fartell spells to override the defaults.
 */
public void
config_fartell_spell()
{
    set_spell_name("ptell");
    set_spell_desc("Talk to someone across a distance");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0); 
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_SIMPLE);    
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_DIVINATION, 10);
    set_spell_fail("Your prayer is unheard.\n");

    set_can_fartell_unmet(1);
}

/*
 * Function:    query_fartell_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_fartell_ingredients(object caster)
{
    return ({ "copper coin" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    // harder to cast on when in poor standings
    if (caster->query_skill(PS_STANDING) < -900)
	set_spell_task(TASK_FORMIDABLE);
    else if (caster->query_skill(PS_STANDING) < -300) 
	set_spell_task(TASK_HARD);

    return 1;
}

/*
 * Function:    resolve_fartell_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_fartell_spell(object caster, mixed * targets, int * resist, int result)
{
    /* intentionally empty */
}

/*
 * Function:    is_valid_fartell_target
 * Description: Called from target_fartell_spell, a customized spell should
 *              mask this and add any restrictions (such as guild members)
 *              on top of the base restrictions in targetting.
 * Returns:     0/1 - not valid/valid target
 */
public int
is_valid_fartell_target(object caster, object target)
{
    if (!objectp(target) || !interactive(target))
        return 0;
    
    return 1;
}

/*
 * Function:    hook_fartell_no_target
 * Description: Override to customize the message for when the caster doesn't
 *              specify a target.
 */
public void
hook_fartell_no_target(object caster)
{
    caster->catch_tell("Who do you want to send a message to?\n");
}

/*
 * Function:    hook_fartell_target_unavailable
 * Description: Override to customize the message for when the target cannot
 *              be reached. This includes invis wizards
 */
public void
hook_fartell_target_unavailable(object caster, string target)
{
    caster->catch_tell("They are not present in the realms.\n");   
}

/*
 * Function:    hook_fartell_target_not_valid
 * Description: Override to customize the message for when the target cannot
 *              be reached because is_valid_fartell_target returns false
 */
public void
hook_fartell_target_not_valid(object caster, string target)
{
    caster->catch_tell("They are not present in the realms.\n");     
}

/*
 * Function:    hook_do_fartell_spell
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_do_fartell_spell(object caster, object target, string message_text)
{
    if(!objectp(target))
    {
        caster->catch_msg("The target of your message doesn't seem " +
            "to be in the realms anymore.\n");
        return;
    }

    target->catch_msg("As if from behind you, you hear " +
	QTNAME(caster) + " whispering:\n\t" + message_text + "\n");
    caster->catch_msg("Across the distance, you whisper to " +
	capitalize(target->query_real_name()) + ":\n\t" +
	message_text + "\n");
    tell_room(environment(caster), QCTNAME(caster)+" closes " +
	HIS(caster) + " eyes and whispers something.\n",
	({ caster }), caster);
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("You cannot complete your prayer without a "+
	"copper coin to sacrifice.\n");
}

/*
 * Function:    hook_send_gmcp_comms
 * Description: Override this hook to customize the message that gets sent
 *              over GMCP.
 */
public void
hook_send_gmcp_comms(object caster, object target, string message_text)
{
    string spell_name   = query_spell_name();
    string caster_name  = target->query_met(caster) ?
                          capitalize(caster->query_real_name()) : "someone";
    string target_name  = capitalize(target->query_real_name());
    
    target->gmcp_comms("fartell", caster_name, "As if from behind you, you " +
    "hear " + caster->query_the_name(target) + " whispering: " +
    message_text + "\n");
    caster->gmcp_comms(spell_name, 0, "Across the distance, you whisper to " +
    target_name + ": " + message_text + "\n");

}