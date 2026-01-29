/*
 * Aitheras Spell for the Elementalist Clerics of Calia
 * 
 * This is the elemental shield spell for the elementalists guild of Calia.
 * It grants regenerative mana shield on the player.
 *
 * Created by Jaacar, January 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/regeneration";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// Defines

// Prototypes

/*
 * Function:    is_worshipper_defensive_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_child_cleric_spell()
{
    return 1;
}

/*
 * Function:    config_regeneration_spell
 * Description: Config function for regeneration spells. Redefine this in your
 *              own regeneration spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_regeneration_spell()
{    
	set_spell_name("aitheras");
    set_spell_desc("Encase with an elemental shield");
    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_ROUTINE);
    
    set_spell_element(SS_ELEMENT_LIFE,  10);
    set_spell_form(SS_FORM_ABJURATION, 25);
    set_spell_combat_aid(25.0);
    set_spell_can_be_renewed(1);
    
    set_spell_target(spell_target_caster);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "spirit_shield_obj");
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float result;
    int penalty = TP->query_prop(CONDUIT_PENALTY);
    
    switch(penalty)
    {
    	case 3:
    		result = 50.0;
    		break;
    	default:
    		result = 100.0;
    		break;
    }
    
    return result;
}

/*
 * Function:    query_regeneration_ingredients
 * Description: This function defines what components are required for
 *              this regeneration spell.
 */
public string *
query_regeneration_ingredients(object caster)
{
    return ({  });
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
        
    // We don't allow the "cast" or "spells" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }
    

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_AITHERAS)
    {
        return 0;
    }
    return 1;
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
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
        caster->catch_tell("You can only invoke the gift of " +
        	query_spell_name() + " upon yourself!\n");
        return 0;
    }

    return 1;    
}

// HOOKS TO BE DEFINED

/*
 * Function name: hook_already_has_spell_object
 * Description:   Checks to see if the target already has one of the 
                  regeneration shields.
 */

public int 
hook_already_has_spell_object(object caster, object target)
{
    write("You are already receiving the benefits of the Aitheras prayer.\n");    
}

/*
 * Function:    resolve_regeneration_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_regeneration_spell(object caster, mixed * targets, int * resist, int result)
{
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
    write("You renew the duration of the Aitheras prayer!\n");
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
    switch (random(2))
    {
    case 0:
        caster_message = "You chant the ancient prayer of Aitheras unto "+
            "Psuchae.\n";
        watcher_message = QCTNAME(caster) + " concentrates as " 
            + caster->query_pronoun() + " begins an ancient chant.\n";
        break;
    
    case 1:
    default:
        caster_message = "You draw upon the the power of " + 
        	"Spirit as you lift up a prayer to Psuchae.\n";
        watcher_message = QCTNAME(caster) + " looks deep in concentration "
            + "as " + caster->query_pronoun() + " lifts up " + 
            caster->query_possessive()
            + " arms to the sky in prayer.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
    int conduit_penalty = caster->query_prop(CONDUIT_PENALTY);
    switch(conduit_penalty)
    {
    	case 1:  // halved conduit gain
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have acted outside of your Vow of "+
		    	"Service. "+
		        "This strains your connection with the Circle and the "+
		        "Conduit.\n\n\n");
    		break;
    	case 2:  // halved conduit gain, double conduit cost
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have deliberately violated your "+
		    	"Vow of Service. "+
		        "The Conduit between the Circle and the Five suffers "+
		        "from your lack of Faith.\n\n\n");
    		break;
    	case 3:  // halved conduit gain, double conduit cost, halved CAID
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have repeatedly violated your "+
		    	"Vow of Service. "+
		        "With such malpractice, your prayers sound weak and "+
		        "hollow.\n\n\n");
    		break;
    	default:
    		GUILD_MANAGER->add_practice_level(caster, 2);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
		    GUILD_MANAGER->add_guild_conduit(2);
    		break;
    }
   
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
    return "none";
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
