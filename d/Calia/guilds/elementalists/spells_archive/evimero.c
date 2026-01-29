/*
 * Haste Spell for the Elemental Worshippers of Calia
 *
 * Created by Petros, December 2010
 *
 * Combat aid modified following global review of layman guilds
 * Arman (AoB) August 2019
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/haste";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// Prototypes
public object * spell_target_haste(object actor, string str);

/*
 * Function:    is_worshipper_power_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_worshipper_power_spell()
{
    return 1;
}

/*
 * Function:    config_haste_spell
 * Description: Config function for haste spells. Redefine this in your
 *              own haste spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_haste_spell()
{
    set_ability_group(GUILD_EW_NAME);
    set_spell_name("evimero");
    set_spell_desc("Increase movement speed");

    set_spell_target(spell_target_haste);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_HARD);    
    set_spell_can_be_renewed(1);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_element(SS_ELEMENT_AIR, 20);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);

    set_spell_combat_aid(30.0);

    // Set the effect object filename
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "evimero_obj");
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    // If the player has both defensive spells on, we reduce the
    // total combat aid provided by this spell.
    if (sizeof(GUILD_MANAGER->query_defensive_spells_active(this_player())) > 1)
    {
        return 100.0 * 15.0 / 30.0;    
    }
    
    return 100.0;
}

public object *
spell_target_haste(object caster, string str)
{
    if (IS_CLERIC(caster))
    {
        return spell_target_one_present_living(caster, str);
    }
    else
    {
        // Worshippers can only cast on themselves.
        return spell_target_caster(caster, str);
    }
}

/*
 * Function:    query_haste_ingredients
 * Description: This function defines what components are required for
 *              this haste spell.
 */
public string *
query_haste_ingredients(object caster)
{
    return ({ "_evimero_component_" });
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
        caster->catch_tell("You can only cast " + query_spell_name() 
            + " on yourself!\n");
        return 0;
    }

    // If either dynami or evimero are active, we are not allowed to cast 
    // this spell
    if (sizeof(GUILD_MANAGER->get_existing_dynami_objects(caster)))
    {
        caster->catch_tell("You cannot invoke evimero while the dynami "+
        	"Elemental Power prayer is active.\n");
        return 0;
    }
        
    if (!GUILD_MANAGER->is_air_carved(caster))
    {
        caster->catch_tell("Without having carved the Word of Power into "+
        	"the Air Dagger, you cannot hope to invoke the gift of "
            + "evimero.\n");
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_EVIMERO)
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
        caster_message = "You bow your head and murmur the ancient mantras "
            + "in prayer to Lady Aeria to grant you the speed of her "
            + "winds.\n";
        watcher_message = QCTNAME(caster) + " bows " + 
        	caster->query_possessive()
            + " head and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You touch your fingers to your forehead as you "
            + "pray to Lady Aeria to grant you the speed of her winds.\n";
        watcher_message = QCTNAME(caster) + " touches " + 
        	caster->query_possessive()
            + " fingers to " + caster->query_possessive() + " forehead and "
            + "concentrates.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
    GUILD_MANAGER->add_practice_level(caster, 5);
    GUILD_MANAGER->add_guild_conduit(5);    
}

/*
 * Function:    resolve_resistance_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_resistance_spell(object caster, mixed * targets, 
	int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already invoked the gift of " + query_spell_name() + "!\n");
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
    write("You renew the duration of evimero!\n");
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
    write("You need the proper ritual component to summon "
        + "the power of " + query_spell_name() + ".\n");
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
    return "chicory, green jade";
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
