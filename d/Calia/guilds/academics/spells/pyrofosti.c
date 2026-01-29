/*
 * Light Spell for the Academy of Elemental Arts
 *
 * Created by Petros, September 2009
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/light";

// Prototypes
public void resolve_light_spell(object caster, mixed * targets, int * resist, int result);

/*
 * Function:    config_light_spell
 * Description: Config function for light spells. Redefine this in your
 *              own light spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_light_spell()
{
    set_spell_name("pyrofosti");
    set_spell_desc("Illuminate your surroundings");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_fail("You complete the spell, but are unable to properly "
        + "control the element of fire.\n");
    set_spell_task(TASK_EASY);    
        
    // Set the effect object filename
    set_spell_object(ACADEMIC_SPELL_OBJS + "pyrofosti_obj");
}

/*
 * Function:    query_fartell_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_light_ingredients(object caster)
{
    return ({ "shard_quartz", "_leftover_eye" });
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
        caster->catch_tell("You can only cast pyrofosti on yourself!\n");
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
    return ACADEMIC_MANAGER->acquired_fire_spell(player);
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
        caster_message = "You hold out a quartz shard and concentrate.\n";
        watcher_message = QCTNAME(caster) + " holds out something in "
            + caster->query_possessive() + " hands and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You draw upon the element of fire as you "
            + "firmly grasp a quartz shard.\n";
        watcher_message = QCTNAME(caster) + " looks deep in concentration "
            + "as " + caster->query_pronoun() + " firmly grasps something "
            + "in " + caster->query_possessive() + " hand.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
    ACADEMIC_MANAGER->add_practice_level(caster, 1);    
}

/*
 * Function:    resolve_light_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_light_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already cast " + query_spell_name() + "!\n");
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
    write("You need both a quartz shard and an eye to summon "
        + "the power of pyrofosti.\n");
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
        "quartz shard, eye"));
}
