/*
 * Stellar Alignment spell for WoHS
 *
 * Coded by Arman 2020.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include "/d/Krynn/guilds/wohs/defs.h"

inherit "/d/Genesis/specials/std/spells/propchange_base";

/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */

public void
config_propchange_spell()
{
    set_spell_name("welunyoweth");
    set_spell_desc("Stellar Alignment - moon phase projection");

    set_spell_element(SS_ELEMENT_AIR,  65);
    set_spell_form(SS_FORM_TRANSMUTATION, 65);
    set_spell_task(TASK_HARD);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_target(spell_target_caster);
   
    set_shadow_filename(WOHS_SPELLS + "objs/stellar_alignment_sh");

}

/*
 * Function:    query_protect_dragonfear_ingredients
 * Description: This function defines what components are required for
 *              this spell.
 */
public string *
query_propchange_ingredients(object caster)
{
    return ({ "grey willow", "moonstone" });
}


/* 
 * Function:    set_input_parameters
 * Description: This function should be overridden by the spell to set
 *              the input parameters that should be passed to the shadow
 *              object.
 */
public void
set_input_parameters(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
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
    return WOHS_MANAGER->query_memorised_spell(player,"welunyoweth_memorised");
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
    string caster_message, watcher_message, moon;
    object target = targets[0];

    switch(QUERY_WOHS_ROBE(caster))
    {
        case "white":
            moon = "Solinari";
            break;
        case "red":
            moon = "Lunitari";
            break;
        case "black":
            moon = "Nuitari";
            break;
        default:
            moon = "Armanari";
            break;
    }

    caster_message = "Your eyes narrow in concentration, your focus deep on " +
        "the phase on your moon of magic, " +moon+ ".\n";
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

    if(caster->query_guild_level_occ() < 9)
    {
        caster->catch_tell("You must be a wizard ranking of the First Circle " +
            "before you are experienced enough to be able to cast this spell!\n");
       return 0;
    }
  
    return 1;
}

/*
 * Function:    hook_describe_cast_propchange
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */

public void
hook_describe_cast_propchange(object caster, object* targets)
{
    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    string moon;

    switch(QUERY_WOHS_ROBE(caster))
    {
        case "white":
            moon = "Solinari";
            break;
        case "red":
            moon = "Lunitari";
            break;
        case "black":
            moon = "Nuitari";
            break;
        default:
            moon = "Armanari";
            break;
    }

    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
            caster->catch_tell("You project the benefits of your moon of magic, " +
                moon+ " upon yourself and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            // caster->catch_tell("You project the benefits of your moon of magic, " +
            //    moon+ " upon yourself.\n");
        }
    }
    else
    {
        // caster->catch_tell("You project the benefits of your moon of magic, " +
        //        moon+ " upon " + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher(QCTNAME(caster) + " projects lunar energies " +
        "of the moon of magic, " +moon+ ".\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " already is projecting " +
        "the benefits of a moon of magic!\n");
}