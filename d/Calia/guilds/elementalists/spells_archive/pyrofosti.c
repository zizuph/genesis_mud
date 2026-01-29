/*
 * Light Spell for the Elemental Worshippers of Calia
 *
 * Created by Petros, December 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/light";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// Prototypes
public void resolve_light_spell(object caster, 
	mixed * targets, int * resist, int result);

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
    set_ability_group(GUILD_EW_NAME);
    set_spell_name("pyrofosti");
    set_spell_desc("Illuminate your surroundings");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);
    
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
    set_spell_task(TASK_EASY);    
        
    // Set the effect object filename
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "pyrofosti_obj");
}

/*
 * Function:    query_light_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_light_ingredients(object caster)
{
    return ({ "_pyrofosti_component_" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!can_cast_elementalist_spell(caster))
    {
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only invoke the gift of pyrofosti "+
        	"upon yourself!\n");
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
    // We don't allow the "cast" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_PYROFOSTI)
    {
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
    switch (random(2))
    {
    case 0:
        caster_message = "You lift up your hands in a prayer to Lord Pyros "
            + "for the gift of pyrofosti.\n";
        watcher_message = QCTNAME(caster) + " lifts up "
            + caster->query_possessive() + " hands and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "Closing your eyes momentarily, you pray for the "
            + "flaming light of Lord Pyros.\n";
        watcher_message = QCTNAME(caster) + " closes " + 
        	caster->query_possessive()
            + " eyes momentarily in prayer.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
    GUILD_MANAGER->add_practice_level(caster, 2);
    GUILD_MANAGER->add_guild_conduit(2);    
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
    write("You are already maintaining the gift of " + query_spell_name() + 
    	"!\n");
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already 
 *              existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You renew your efforts to maintain the gift of pyrofosti!\n");
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
    write("You need the proper ritual component to "
        + "invoke the prayer of pyrofosti.\n");
}


/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "cranberry, rose quartz";
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "prayers" is used.
 */
public void
list_spells()
{
    string ingredients_description = query_spell_ingredients_description();
    if (!strlen(ingredients_description))
    {
        ingredients_description = "none";
    }
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        ingredients_description));
}
