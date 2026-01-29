/*
 * Featherweight spell for SOHM
 *
 * Coded by Arman 2017.
 *
 * Default weight factor set is 140, which equates to 5 combat aid.
 *  - Arman, January 2022.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "featherweight";

#include "sohm_spell_functions.h"

/*
 * Function:    config_featherweight_spell
 * Description: Config function for featherweight spells. Redefine this in your
 *              own featherweight spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_featherweight_spell()
{
    set_spell_name("nasirmitne");
    set_spell_desc("Featherweight - transmute the weight of items you carry");

    set_spell_element(SS_ELEMENT_AIR,  40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_EASY);
   
    set_spell_object(SOHM_SPELL_OBJS + "featherweight_obj");
}

/*
 * Function:    query_featherweight_ingredients
 * Description: This function defines what components are required for
 *              this featherweight spell.
 */
public string *
query_featherweight_ingredients(object caster)
{
    return ({ "fiddlehead" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"nasirmitne_memorised");
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

    string who;
    if(target == caster)
    {
      who = "you";
    }
    else
    {
      who = COMPOSITE_LIVE(targets);
    }

    caster_message = "Your eyes narrow in concentration as you begin reciting " +
        "words of magic that will transmute the very nature of physical items, " +
        "making them lighter for " +who+ " to carry.\n";
    watcher_message = QCTNAME(caster) + " narrows " + caster->query_possessive() + 
        " eyes in concentration and begins reciting mystical words of magic.\n";
        
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

    if(query_maintained_defensive_caid_spells(caster, "minor") > 2)
    {
        // Allow spell to be renewed
        if("/d/Krynn/guilds/sohm/spells/featherweight"->has_spell_object(caster))
            return 1;

	caster->catch_tell("You can only maintain three minor spells " +
           "that provide combat utility at any time.\n");
	return 0; 
    }
  
    return 1;
}

/*
 * Function:    resolve_featherweight_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_featherweight_spell(object caster, mixed * targets, int * resist, int result) 
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target)
    {
        write("Your load is already as light as a feather!\n");
    }
    else
    {
        caster->catch_msg("You are already maintaining the ability to lighten " 
            + QTPNAME(target) + " burdens.\n");
    }
}

/*
 * Function:    hook_renew_spell_object 
 * Description: Message to give when the spell is recast onto an already existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You renew the duration of the featherweight spell!\n");
}