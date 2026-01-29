/*
 * Scry Spell for School of High Magic
 *
 * Coded by Arman 2016.
 * 
 */
 
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "scry";

/*
 * Function:    query_scry_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_scry_ingredients(object caster)
{
    return ({ "sargassum", "bull kelp" });
}

/*
 * Function:    config_scry_spell
 * Description: Config function for scry spells. Redefine this in your
 *              own scry spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_scry_spell()
{
    set_spell_name("ehtahxiekiv");
    set_spell_desc("Divine location - scry someone's location");

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);    
    set_spell_element(SS_ELEMENT_WATER, 40);
    set_spell_form(SS_FORM_DIVINATION, 50);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_ingredients(query_scry_ingredients);
    
}

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
    return SOHM_MANAGER->query_memorised_spell(player,"ehtahxiekiv_memorised");
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
        caster->catch_tell("You are not a student of the School of High Magic!\n");
        return 0;
    }
*/
    
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

        caster_message = "You close your eyes and whisper the words of magic " +
           "'Ehtah Xiekiv!' and send your senses out of your body and across " +
           "the realms.\n";
        watcher_message = QCTNAME(caster)+" closes "+caster->query_possessive()+ 
           " eyes and whispers words of magic before falling in to a trance.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
}

/*
 * Function:    hook_no_scry_message
 * Description: When it is not possible to scry, for whatever reason,
 *              this message is given. This applies to no-scry properties
 *              as well as trying to scry a wizard or someone linkdead.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_no_scry_message(object caster, object target)
{
    caster->catch_tell("Your attempt to divine the location of " +
         "your target is obscured by a mysterious veil.\n");    
}

/*
 * Function:    hook_scry_success
 * Description: When there is a successful scry, a message is prepended
 *              before the room descriptions. This is where you
 *              customize that message.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 *              brief  - whether the description will be brief or not
 */
public void
hook_scry_success(object caster, object target, int brief)
{
    if (brief)
    {
        caster->catch_tell("You vaguely sense your target's surroundings "
            + "as through their perceptions.\n");
    }
    else
    {
        caster->catch_tell("You see your target's surroundings, as "
            + "through their eyes.\n");
    }

    tell_room(environment(caster), QCTNAME(caster) + " leaves " + 
      caster->query_possessive()+ " trance and opens " +
      caster->query_possessive()+" eyes, more knowledgeable than " +
      "before.\n", ({ caster }), caster);
}
