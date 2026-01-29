/*
 * Mana regeneration spell, based on the regeneration base spell.
 *
 * The formula for mana regeneration is incorporated into the 
 * regen_mana_obj.c, with the regeneration rate taking into account
 * spell element skill (defaults to water), whether you are in
 * combat, your wisdom, and also your 'soaked' level (water consumption
 * improves mana regen).
 *
 * In general magic guilds should restrict these sort of spells, as
 * one of the principles justifying magic guilds' extra combat aid
 * is that there are drawbacks for casting such as mana usage.
 *
 * This sort of spell should only allow a temporary extension of casting
 * time before mana pool is exhausted, rather than a spell that allows
 * continuous casting of spells such as harm. 
 *
 * Maximum allowable combat aid for this spell is 25. This sort of spell
 * isn't appropriate for layman or racial guilds in the majority of 
 * circumstances.
 *
 * Arman - October 2017
 */

#pragma strict_types

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes

public void resolve_regen_mana_spell(object caster, mixed * targets, int * resist, int result);


#define MANA_REGEN_OBJECT  (SPELL_DIR + "unfinished/regen_mana_obj")
#define MAX_MANA_REGEN_CAID     25.0

/*
 * Function:    config_regen_mana_spell
 * Description: Config function for mana regeneration spells. Redefine this in your
 *              own at will spells to override the defaults.
 */
public varargs void
config_regen_mana_spell()
{
    set_spell_combat_aid(MAX_MANA_REGEN_CAID);

    // Spell effect object
    set_spell_object(MANA_REGEN_OBJECT);

}

/*
 * Function:    query_regen_mana_ingredients
 * Description: This function defines what components are required for
 *              this regeneration spell.
 */

public string *
query_regen_mana_ingredients(object caster)
{
    return ({ });
}

private nomask void
config_required_parameters()
{
    if (query_spell_combat_aid() >= MAX_MANA_REGEN_CAID)
    {
	// Mana regen a maximum combat aid of MAX_MANA_REGEN_CAID. This will
	// be enforced in this code.

	set_spell_combat_aid(MAX_MANA_REGEN_CAID);
    }

}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("manaregen");
    set_spell_desc("Mana regeneration");

    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_offensive(0);
    set_spell_peaceful(1);
    set_spell_can_be_renewed(1);

    // Can only cast regen_mana on themself. In most cases this
    // shouldn't be changed.
    set_spell_target(spell_target_caster);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_spell_ingredients(query_regen_mana_ingredients);

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.

    set_spell_element(SS_ELEMENT_AIR,  30);
    set_spell_form(SS_FORM_TRANSMUTATION, 30);

    config_regen_mana_spell();

    // Call this after the config_mana_regen_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_regen_mana_spell(caster, targets, resist, result);

    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    float aid = query_spell_combat_aid(); // effect uses combat aid

    if (query_spell_can_be_renewed())
    {
	mixed * renewed_targets = ({ });
	mixed * remaining_targets = ({ });
	int * remaining_resists = ({ });
	for (int index = 0; index < sizeof(targets); ++index)
	{
	    object * existing_objs = get_existing_spell_objects(targets[index]);
	    if (sizeof(existing_objs))
	    {
		existing_objs->renew_spell_duration();
		renewed_targets += ({ targets[index] });
	    }
	    else
	    {
		remaining_targets += ({ targets[index] });
		remaining_resists += ({ resist[index] });
	    }
	}
	if (sizeof(renewed_targets))
	{
	    hook_renew_spell_object(caster, renewed_targets);
	}
	if (sizeof(remaining_targets))
	{
	    make_spell_object(query_spell_object(), caster, remaining_targets,
	      remaining_resists, result, aid);    
	}
    }
    else
    {
	make_spell_object(query_spell_object(), caster, targets, resist, result, aid);
    }
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
	return result;
    }

    if (!query_spell_can_be_renewed())
    {
        // The same resistance spell cannot be stacked.
        foreach (object target : targets)
        {
            if (has_spell_object(target))
            {
                hook_already_has_spell_object(caster, target);
                return 0;
            }
        }
    }

    return result;    
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

    return 1;
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

    caster_message = "You rapidly trace a sygil of protection in the air while chanting " +
    "'Manashield!'\n";
    watcher_message = QCTNAME(caster) + " rapidly traces a complicated sygil in the air " +
    "while chanting mystical words of magic.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

// HOOKS TO BE DEFINED
/*
 * Function:    resolve_regen_mana_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_regen_mana_spell(object caster, mixed * targets, int * resist, int result)
{

}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("Your mana regeneration is already enhanced!\n");
}
