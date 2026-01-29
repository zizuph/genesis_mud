/*
 * Find a target's real name
 * Uses the detect alignment base.
 *
 * Created by Jaacar, January 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <files.h>
#include <flags.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/alignment";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

/*
 * Function:    is_master_cleric_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_master_cleric_spell()
{
    return 1;
}

/*
 * Function:    config_alignment_spell
 * Description: Config function for alignment spells. Redefine this in your
 *              own alignment spells to override the defaults.
 *
 * Arguments:   None
 * Returns:     None
 */

public void
config_alignment_spell()
{
    set_spell_name("anagnorizo");
    set_spell_desc("Discover true identity");

    set_spell_element(SS_ELEMENT_LIFE, 30);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_task(TASK_HARD);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

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
    string caster_message = "You close your eyes briefly and concentrate "+
        "on the energies Psuchae has granted you.\n";
    string watcher_message = QCTNAME(caster) + " closes "
        + caster->query_possessive() + " eyes briefly and concentrates.\n";
    
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
    int conduit_penalty = caster->query_prop(CONDUIT_PENALTY);
    
    switch(conduit_penalty)
    {
    	case 1:  // halved conduit gain
    		GUILD_MANAGER->add_practice_level(caster, 2);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
		    GUILD_MANAGER->add_guild_conduit(2);
		    caster->catch_tell("\n\nYou have acted outside of your Vow of "+
		        "Service. This strains your connection with the Circle and "+
		        "the Conduit.\n\n\n");
    		break;
    	case 2:  // halved conduit gain, double conduit cost
    		GUILD_MANAGER->add_practice_level(caster, 2);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
		    GUILD_MANAGER->add_guild_conduit(2);
		    caster->catch_tell("\n\nYou have deliberately violated your Vow "+
		        "of Service. The Conduit between the Circle and the Five "+
		        "suffers from your lack of Faith.\n\n\n");
    		break;
    	case 3:  // halved conduit gain, double conduit cost, halved CAID
    		GUILD_MANAGER->add_practice_level(caster, 2);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
		    GUILD_MANAGER->add_guild_conduit(2);
		    caster->catch_tell("\n\nYou have repeatedly violated your Vow "+
		        "of Service. With such malpractice, your prayers sound "+
		        "weak and hollow.\n\n\n");
    		break;
    	default:
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
    		break;
    }
}

/*
 * Function name: resolve_alignment_spell 
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed* targets  - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_alignment_spell(object caster, mixed* targets, int* resist, int result)
{
}

/**
 * Function name : hook_fail_target_not_present
 * Description   : Writes output to caster when the target is not present.
 * Arguments     : object caster - the person casting the alignment spell.
 *               : object target - the specified target of the alignment spell.
 */
 
public void
hook_fail_target_not_present(object caster, object target)
{
    caster->catch_tell("Your specified target is not here to divine their "+
        "name.\n");
}

/*
 * Function:    query_alignment_ingredients
 * Description: This function defines what components are required for
 *              this alignment spell.
 */
public string *
query_alignment_ingredients(object caster)
{
    string caster = TP->query_real_name();
    string element = GUILD_MANAGER->query_primary_element(caster);
    
    switch(element)
    {
        case "fire":
            return ({ "_pyros_component_" });
            break;
        
        case "air":
            return ({  });
            break;
            
        case "water":
            return ({ "_diabrecho_component_" });
            break;
        
        case "earth":
            return ({ "_gu_component_" });
            break;
            
        case "life":
            return ({ "_psuchae_component_" });
            break;
    }
}

/*
 * Function name : hook_report_alignment
 * Description   : Hook method to be masked to provide your own descriptions
 *                 of the alignment.
 *
 * Arguments  : object caster        - The caster of the spell.
 *            : object target        - The target of the spell, who to check
 *                                     the alignment for.
 *            : int target_alignment - The alignment of the target.
 *            : int result           - Result of the spell cast, how well 
 *                                     it was cast.
 */
public void
hook_report_alignment(object caster, object target, int target_alignment, int result)
{
    caster->catch_msg("After probing " + target->query_possessive() + 
        " mind, you come to the realization that "+
        target->query_possessive() + " name is "+
        capitalize(target->query_real_name()) + ".\n");

    if (interactive(target))
    {
        caster->add_introduced(target->query_real_name());
    }
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

    if (player->query_wiz_level())
    {
        // Wizards get all spells
        return 1;
    }
    
    // We don't allow the "cast" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }


    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_ANAGNORIZO)
    {
        return 0;
    }

    // Only master clerics and higher get this spell
    if (GUILD_MANAGER->query_is_child_cleric(player))
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    hook_alignment_sucess
 * Description: Mask this function to change the description of when
 *              the object is successfully identified.
 */
public void
hook_alignment_success(object caster, object target, string id_message, int result)
{
    if (!objectp(caster) || !objectp(target))
    {
        return;
    }
    caster->catch_tell(id_message);

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
    
    object mandala = present("_elemental_guild_mandala", caster);
    if (!mandala)
    {
        write("You cannot use this prayer without your sacred mandala!\n");
        return 0;
    }
    
    if (present("_elemental_child_mandala", caster))
    {
    	write("You cannot use this prayer without carving the Word of Power "+
    	    "into your sacred mandala!\n");
    	return 0;
    }

    object target = targets[0];

    if (!IS_LIVING_OBJECT(target))
    {
        caster->catch_tell("You can only cast this spell on living " +
           "beings.\n");
        return 0;
    }
    
    if (!interactive(target) &&
        find_living(target->query_real_name()) != target)
    {
        caster->catch_tell("You probe the mind of the "+
            target->query_nonmet_name() + ", but discover no name.\n");
        return 0;
    }
  
    return 1;
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
    string caster = TP->query_real_name();
    string element = GUILD_MANAGER->query_primary_element(caster);
    
    switch(element)
    {
        case "fire":
            return "pyros component (fireweed, ruby shard)";
            break;
        
        case "air":
            return "none";
            break;
            
        case "water":
            return "diabrecho component (sargassum, sapphire shard)";
            break;
        
        case "earth":
            return "gu component (cladina, emerald shard)";
            break;
            
        case "life":
            return "psuchae component (drakeroot, alexandrite shard)";
            break;
    }
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
