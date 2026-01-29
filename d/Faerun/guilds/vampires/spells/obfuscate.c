/*
 * Invisibility spell for Vampires
 * 
 * Nerull 2021
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "invisibility";

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "../guild.h"


/*
 * Function:    config_invisibility_spell
 * Description: Config function for invisibility spells. Redefine this in your
 *              own spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_invisibility_spell()
{
    set_spell_name("obfuscate");
    set_spell_desc(" - Turns the vampire invisible to the normal eye");

    set_spell_target(spell_target_caster);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_DIFFICULT);
    
    set_spell_can_be_renewed(1);

    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);
    
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_shadow_filename(VAMPIRES_SPELLOB_DIR + "obfuscate_sh");
}


/*
 * Function:    query_evade_ingredients
 * Description: This function defines what components are required for
 *              this evade spell.
 */
public string *
query_invisitibility_ingredients(object caster)
{
    return ({ });
}


/*
* Function:    query_spell_can_be_learned
* Description: Place restrictions on whether this spell can be used
*              by the guild member.
*/
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
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 3)
    {
         return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 2)
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
    
    // We allow ethereal if there is no player fighting going on.
    if (!caster->query_relaxed_from_combat())
    {
        write("You are still too active from combat to use this spell.\n");
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
    
    // Blood-drain
    int bloodamount = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());     
    bloodamount = bloodamount - OBFUSCATE_COST;   
    VAMPIRES_MAPPINGS->set_thirst_gauge(caster->query_name(), bloodamount);

    caster_message = "You concentrate on the powers of the blood!\n";
           
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}


/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg("You are already invisible!\n");
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
    write("You are missing an ingredient to cast Obfuscate.\n");
}

