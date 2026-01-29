/*
 * By Nerull, June 2021
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "fartell";

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "../guild.h"

/*
 * Function:    config_fartell_spell
 * Description: Config function for fartell spells. Redefine this in your
 *              own fartell spells to override the defaults.
 */
public void
config_fartell_spell()
{
    set_spell_name("childwhisper");
    set_spell_desc(" - send a telepathic whisper to your vampire child");
    set_spell_vocal(0);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_1);

    set_spell_task(TASK_ROUTINE);    
    set_spell_element(SS_ELEMENT_WATER, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 10);
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
    return ({  });
}


public int
query_spell_can_be_learned(object player)
{
    setuid();
    seteuid(getuid());

    if (!objectp(player))
    {
        return 0;
    }

    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) > 0)
    {
         return 1;
    }
    
    return 0;
}


public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!present("_vampire_powers_unlock_ob", caster))
    {
        caster->catch_tell("You are too weak! You "
        +"need to rise from a coffin in order to use this gift.\n");
        
        return 0;
    }
    
    int check = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());
    
    if (check < ABILITY_THRESHOLD)
    {
        caster->catch_tell("The thirst is too overwhelming for you to "
        +"concentrate. Aquire more blood!\n");
        
        return 0;
    }
    
    if (caster->query_ethereal() == 1)
    {
        caster->catch_tell("You are in the ethereal realm. This spell "
        +"doesn't work there.\n");
        
        return 0;
    }
    
    return 1;
}


// HOOKS TO BE DEFINED
/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;
    
    caster_message = "You concentrate on the powers of the blood!\n";
    
    caster->catch_tell(caster_message);
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
    {
	    return 0;
    }
    
    if(target->query_wiz_level())
    {
	    return 0;
    }
    
    string qsire = capitalize(target->query_sire());
    
    if (qsire != caster->query_name())
    {
        caster->catch_tell("That person is not your child.\n");
    
        return 0;
    }
    
    return 1;
}


/*
 * Function:    hook_fartell_target_unavailable
 * Description: Override to customize the message for when the target cannot
 *              be reached. This includes invis wizards
 */
public void
hook_fartell_target_unavailable(object caster, string target)
{
    caster->catch_tell("You do not sense " + capitalize(LANG_POSS(target)) 
      + " presence in the realms.\n");    
}


/*
 * Function:    hook_fartell_target_not_valid
 * Description: Override to customize the message for when the target cannot
 *              be reached because is_valid_fartell_target returns false
 */
public void
hook_fartell_target_not_valid(object caster, string target)
{
    caster->catch_tell(capitalize(target) + " is not " +
      "contactable.\n");    
}


/*
 * Function:    hook_send_gmcp_comms
 * Description: Override this hook to customize the message that gets sent
 *              over GMCP.
 */
public void
hook_send_gmcp_comms(object caster, object target, string message_text)
{
    string spell_name = query_spell_name();
    
    string caster_name = target->query_met(caster) ? capitalize(caster->query_real_name()) :"someone";
    string target_name = capitalize(target->query_real_name());
    
    caster->gmcp_comms(spell_name, 0, "You telepathically whisper to "
    + target_name + ": " +message_text);
        
        
    target->gmcp_comms("fartell", caster_name, "A voice whispers in your mind:\n\t"
      + message_text);
}


/*
 * Function:    hook_do_fartell_spell
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_do_fartell_spell(object caster, object target, string message_text)
{
    target->catch_msg("A voice whispers in your mind:\n\t" 
      + message_text + "\n");
      
    caster->catch_msg("You telepathically whisper to " + capitalize(target->query_real_name())+ ":\n\t" 
      + message_text + "\n");
}


/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
}


/*
 * Function:    hook_fartell_no_message
 * Description: Override to customize the message for when the caster doesn't
 *              specify a text to send.
 */
public void
hook_fartell_no_message(object caster)
{
    caster->catch_tell("What message do you want to telephatically "
    +"whisper? (" + query_verb() + " <recipient> <message>)\n");
}


/*
 * Function:    hook_fartell_no_target
 * Description: Override to customize the message for when the caster doesn't
 *              specify a target.
 */
public void
hook_fartell_no_target(object caster)
{
    caster->catch_tell("Who do you want to telephatically whisper "
    +"a message to? (" + query_verb() + " <recipient> <message>)\n");
}
