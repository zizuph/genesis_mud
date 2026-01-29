/*
 * Invisibility spell for SoHM
 * 
 * Created by Arman 2016
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "/d/Krynn/guilds/sohm/spells/defs.h"

inherit "/d/Genesis/specials/std/spells/invisibility";

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
    set_spell_name("zhinpersvek");
    set_spell_desc("Shadow walk - cloak yourself in shadows, " +
        "becoming invisible.");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_offensive(0);
    set_spell_peaceful(1);
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_ILLUSION, 50);
    set_spell_task(TASK_HARD);   

    // Can only cast shadow walk on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_shadow_filename(SOHM_SPELL_OBJS + "invisibility_sh");
}

/*
 * Function:    query_evade_ingredients
 * Description: This function defines what components are required for
 *              this evade spell.
 */
public string *
query_invisitibility_ingredients(object caster)
{
    return ({ "snake skin","blung"  });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only cast shadow walk on yourself!\n");
        return 0;
    }
        
    return 1;
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
    
    // When holding the spellbook it can be cast
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

        caster_message = "You crouch down furtively and begin making " +
           "grasping motions with your hands while reciting magical " +
           "words of deception and confusion - 'Zhin Persvek!'\n";
        watcher_message = QCTNAME(caster) + " crouches down furtively " +
           "and makes grasping motions with " +caster->query_possessive()+ 
           " hands while reciting mystical words of magic.\n";
        
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
    caster->catch_msg("You are already invisible in the shadow realms!\n");
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
    write("You are missing an ingredient to cast the shadow walk spell.\n");
}

