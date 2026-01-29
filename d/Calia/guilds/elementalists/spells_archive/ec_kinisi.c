/*
 * Deliver Water Globe Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, February 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

inherit (ELEMENTALIST_SPELLS + "standard_deliver");
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
 * Function:    config_scry_spell
 * Description: Config function for scry spells. Redefine this in your
 *              own scry spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_scry_spell()
{
    set_spell_name("kinisi");
    set_spell_desc("Deliver water globe");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_ROUTINE);    
    set_spell_element(SS_ELEMENT_WATER, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_ingredients(query_scry_ingredients);
    
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_KINISI)
    {
        return 0;
    }

    // Only master clerics and higher get this spell
    if (GUILD_MANAGER->query_is_child_cleric(player))
    {
        return 0;
    }
    
    // Only water clerics get this spell
    if (GUILD_MANAGER->query_primary_element(player) != "water")
    {
        return 0;
    }    

    return 1;
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
    
    if (!present("_cleric_water_globe", caster))
    {
    	caster->catch_msg("You do not have a water globe to deliver. "+
    	    "(Use 'eglobe' to summon one)\n");
    	return 0;
    }
    
    if (!caster->query_met(targets[0]))
    {
    	caster->catch_msg("You have not met anyone by that name.\n");
    	return 0;
    }
    
    if (!interactive(targets[0]))
    {
    	caster->catch_msg("You can only deliver the water globe to "+
    	    "players.\n");
    	    return 0;
    }
    
    if (targets[0]->query_linkdead())
    {
    	caster->catch_msg("You cannot deliver the water globe to "+
    	    "linkdead players.\n");
    	return 0;
    }
    
    if (targets[0] == caster)
    {
    	caster->catch_msg("You cannot deliver the water globe to yourself.\n");
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

    caster_message = "You close your eyes and concentrate on locating "+
        "your target.\n";
    watcher_message = QCTNAME(caster)+" closes "+caster->query_possessive()+ 
       " eyes.\n";
        
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
		        "Service. "+
		        "This strains your connection with the Circle and the "+
		        "Conduit.\n\n\n");
    		break;
    	case 2:  // halved conduit gain, double conduit cost
    		GUILD_MANAGER->add_practice_level(caster, 2);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
		    GUILD_MANAGER->add_guild_conduit(2);
		    caster->catch_tell("\n\nYou have deliberately violated your "+
		        "Vow of Service. "+
		        "The Conduit between the Circle and the Five suffers from "+
		        "your lack of Faith.\n\n\n");
    		break;
    	case 3:  // halved conduit gain, double conduit cost, halved CAID
    		GUILD_MANAGER->add_practice_level(caster, 2);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
		    GUILD_MANAGER->add_guild_conduit(2);
		    caster->catch_tell("\n\nYou have repeatedly violated your "+
		        "Vow of Service. "+
		        "With such malpractice, your prayers sound weak and "+
		        "hollow.\n\n\n");
    		break;
    	default:
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
    		break;
    }
}

/*
 * Function:    hook_no_scry_message
 * Description: When it is not possible to scry, for whatever reason,
 *              this message is given. This applies to no-scry properties
 *              as well as trying to scry a wizard or someone linkdead.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_no_scry_message(object caster, object target)
{
    caster->catch_tell("Your cannot seem to locate your target.\n");    
}

/*
 * Function:    hook_scry_success
 * Description: When there is a successful scry, a message is prepended
 *              before the room descriptions. This is where you
 *              customize that message.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 *              brief  - whether the description will be brief or not
 */
public void
hook_scry_success(object caster, object target, int brief)
{
	object water_globe;
    caster->catch_tell("As you open your eyes, the water globe you "+
        "are carrying disappears and is delivered to "+
        capitalize(target->query_real_name()) + ".\n");

    tell_room(environment(caster), QCTNAME(caster) + " opens " +
    	caster->query_possessive()+" eyes.\n", ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
    water_globe = present("_cleric_water_globe", caster);
    water_globe->move(target,1);
    target->catch_tell("A water globe appears in your hands. Somehow "+
        "you realize that you had best pick up the contents of it "+
        "as soon as possible. When you have all of the items, you may "+
        "<squish globe> to get rid of it.\n");   
}

/*
 * Function:    query_scry_ingredients
 * Description: This function defines what components are required for
 *              this scry spell.
 */
public string *
query_scry_ingredients(object caster)
{
    return ({  });
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
