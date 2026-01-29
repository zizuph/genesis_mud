/*
 * Stoneskin Spell for Academy of Elemental Arts
 * 
 * Created by Petros, September 2009
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/stoneskin";

/*
 * Function:    config_stoneskin_spell
 * Description: Config function for stoneskin spells. Redefine this in your
 *              own stoneskin spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_stoneskin_spell()
{
    set_spell_name("lithodermu");
    set_spell_desc("Transform your skin to stone");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_combat_aid(25.0);
    set_spell_fail("You complete the spell, but are unable to properly "
        + "control the element of earth.\n");

    set_spell_element(SS_ELEMENT_EARTH, 20);
    set_spell_form(SS_FORM_TRANSMUTATION, 20);
    set_spell_task(TASK_EASY);    

    // Academics can only cast stoneskin on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(ACADEMIC_SPELL_OBJS + "lithodermu_obj");
}

/*
 * Function:    query_stoneskin_ingredients
 * Description: This function defines what components are required for
 *              this stoneskin spell.
 */
public string *
query_stoneskin_ingredients(object caster)
{
    // Onyx gem provides the "earth" element. Chicory provides the
    // constitution (fatigue) generating factor.
    return ({ "shard_onyx", "chicory" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!IS_MEMBER(caster))
    {
        caster->catch_tell("You are not a member of the Academy!\n");
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only cast lithodermu on yourself!\n");
        return 0;
    }
    
    if (ACADEMIC_MANAGER->is_casting_banned(caster))
    {
        caster->catch_tell("You have been banned from casting combat "
            + "spells for breaking the rules. Please see <help academic "
            + "rules>.\n");
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
    
    setuid();
    seteuid(getuid());
    return ACADEMIC_MANAGER->acquired_earth_spell(player);
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
    switch (random(2))
    {
    case 0:
        caster_message = "You close your eyes and draw upon the element "
            + "of earth while focusing deeply upon the onyx shard.\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You crouch down, place both your palms on the "
            + "ground, and draw energy from the ground.\n";
        watcher_message = QCTNAME(caster) + " crouches down and places "
            + "both hands upon the ground.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
    ACADEMIC_MANAGER->add_practice_level(caster, 2);    
}

/*
 * Function:    resolve_stoneskin_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_stoneskin_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("Your skin has already been transformed by the earthly elemental "
        + "power of lithodermu!\n");
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
    write("You need both an onyx shard and a chicory herb to utilize "
        + "the power of lithodermu.\n");
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used.
 */
public void
list_spells()
{
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        "onyx shard, chicory"));
}
