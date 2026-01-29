/*
 * Enchant Weapon Spell for SOHM
 *
 * Coded by Arman 2016.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "shadow";

#include "sohm_spell_functions.h"

#define ACTIVE_ENCHANTMENT "_sohm_enchant_weapon_active"

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shadow_spell()
{
    set_spell_name("levexlaraek");
    set_spell_desc("Enchant weapon - animate your weapon to assist in battles");

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH,  40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);

    set_ability_stats(STAT_WEIGHTING);

    // Added for the purpose of calculating sustained mana
    set_spell_combat_aid(40.0);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);

    set_spell_target(spell_target_one_present_non_living);
   
    set_shadow_filename(SOHM_SPELL_OBJS + "enchant_weapon_sh");
}

/*
 * Function:    is_valid_weapon_for_spell
 * Description: This returns whether this particular weapon is valid to
 *              be shadowed. This should be masked to match
 *              what type of weapons are valid to use for shadowing.
 *
 * Arguments: object obj - the object to check for validity.
 * Returns: integer, 0 for invalid, 1 for valid.
 */
public int
is_valid_weapon_for_spell(object weapon)
{
    if (!objectp(weapon))
    {
        return 0;
    }
    return 1;
}

/*
 * Function:    resolve_shadow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
}

/*
 * Function:    query_shadow_ingredients
 * Description: This function defines what components are required for
 *              this shadow spell.
 */
public string *
query_shadow_ingredients(object caster)
{
    return ({"tuo","cattail"});
}


/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"levexlaraek_memorised");
}

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
    object target = targets[0];

        caster_message = "You focus on your " +target->short()+ " and begin reciting "
            + "words of magic, 'Levex Laraek!'\n";
        watcher_message = QCTNAME(caster) + " focuses on "
            + caster->query_possessive() + " " + target->short() + " and begins reciting " +
              "mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

/* Allowing these spells to potentially be more widely used than just SoHM
    
    if (!IS_MEMBER(caster))
    {
        caster->catch_tell("You are not a Student of High Magic!\n");
        return 0;
    }
    
    if (SOHM_MANAGER->is_casting_banned(caster))
    {
        caster->catch_tell("You have been banned from casting combat "
            + "spells for breaking the rules.\n");
        return 0;
    }

*/

    if (!IS_WEAPON_OBJECT(targets[0]))
    {
        caster->catch_tell("You can only cast this spell on weapons.\n");
        return 0;
    }
  
    if (!is_valid_weapon_for_spell(targets[0]))
    {
        caster->catch_tell("You can only cast this enchantment on weapons.\n");
        return 0;
    }
    
    if (!targets[0]->query_wielded())
    {
        object weapon = targets[0];

        caster->catch_tell("Your " + weapon->short() + " must be wielded during enchantment.\n");
	return 0;
    }

    if(targets[0]->query_prop(ACTIVE_ENCHANTMENT))
    {
        caster->catch_tell("You can only maintain one enchantment on this item " +
             "at a time.\n");
        return 0;
    }

    if(query_maintained_defensive_caid_spells(caster, "lesser") > 1)
    {
        //Allow spell to be renewed
        if(caster->query_prop("_sohm_enchant_weapon_active"))
            return 1;

	caster->catch_tell("You can only maintain two lesser spells " +
           "that provide combat utility at any time.\n");
	return 0; 
    }
  
    return 1;
}