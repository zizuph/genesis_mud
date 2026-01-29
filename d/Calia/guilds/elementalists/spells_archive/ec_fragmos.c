/*
 * Slow Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, February 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/slow";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

/*
 * Function:    is_master_guru_cleric_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_master_guru_cleric_spell()
{
    return 1;
}

/*
 * Function:    config_slow_spell
 * Description: Config function for slow spells. Redefine this in your
 *              own slow spells to override the defaults.
 */
public void
config_slow_spell()
{
    set_spell_name("fragmos");
    set_spell_desc("Slow down the movement of your enemy");
    
    set_spell_element(SS_ELEMENT_EARTH, 35);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_task(TASK_ROUTINE);

    set_spell_stationary(0);    
    set_spell_offensive(1);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_ingredients(query_slow_ingredients);
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "fragmos_obj");    
    
    set_slow_interval(2.5);
}

public int
query_spell_effect_power()
{
	int result;
	string primary_element;
    string caster = this_player()->query_real_name();
    
    // What is their primary element?
    primary_element = GUILD_MANAGER->query_primary_element(caster);
    
    switch(primary_element)
    {
	    case "fire":
	    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
	    		result = 25;
	    	else
	        	result = 50;
	        break;
	    
	    case "earth":
	    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
	    		result = 30;
	    	else
	        	result = 60;
	        break;
	    
	    case "water":
	    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
	    		result = 30;
	    	else
	        	result = 60;
	        break;
	    
	    case "air":
	    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
	    		result = 30;
	    	else
	        	result = 60;
	        break;
	        
	    case "life":
	    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
	    		result = 30;
	    	else
	        	result = 60;
	        break;
	    
	    default:
	    	// If all else fails, give the lowest CAID
	    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
	    		result = 25;
	    	else
	    		result = 50;
	    	break;
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_FRAGMOS)
    {
        return 0;
    }

    // Only master clerics and higher get this spell
    if (GUILD_MANAGER->query_is_child_cleric(player))
    {
        return 0;
    }

    // Only players who have finished the Guru quest get this spell
    if (!player->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    {
        return 0;
    }       

    return 1;
}

/*
 * Function:    query_slow_ingredients
 * Description: This function defines what components are required for
 *              this slow spell.
 */
public string * 
query_slow_ingredients(object caster)
{
    return ({ "_fragmos_component_" });
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

    // The slow spell cannot be cast if it is already in effect. At some
    // point, if this spell is going to be mass cast, we should allow the
    // spell to be cast even if some of the targets have the slow spell on.
    // We just need to be careful not to stack the effects.
    foreach (object target : targets)
    {
        if (has_spell_object(target))
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }       	 
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

    caster_message = "You close your eyes and concentrate on "+
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
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
		    caster->catch_tell("\n\nYou have acted outside of your "+
		        "Vow of Service. "+
		        "This strains your connection with the Circle and the "+
		        "Conduit.\n\n\n");
    		break;
    	case 2:  // halved conduit gain, double conduit cost
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
		    caster->catch_tell("\n\nYou have deliberately violated your "+
		        "Vow of Service. "+
		        "The Conduit between the Circle and the Five suffers from "+
		        "your lack of Faith.\n\n\n");
    		break;
    	case 3:  // halved conduit gain, double conduit cost, halved CAID
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
		    caster->catch_tell("\n\nYou have repeatedly violated your "+
		        "Vow of Service. "+
		        "With such malpractice, your prayers sound weak and "+
		        "hollow.\n\n\n");
    		break;
    	default:
    		GUILD_MANAGER->add_practice_level(caster, 10);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 10);
		    GUILD_MANAGER->add_guild_conduit(10);
    		break;
    }
}

/*
 * Function:    hook_no_slow_message
 * Description: When it is not possible to slow, for whatever reason,
 *              this message is given.
 * Arguments:   caster - person casting the spell
 *              target - the person being slow
 */
public void
hook_no_slow_message(object caster, object target)
{
    caster->catch_tell("Your cannot seem to locate your target.\n");    
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " has already been "+
            "slowed!\n");
    }
}

/*
 * Function:    resolve_slow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_slow_spell(object caster, mixed *targets, int * resist, int result)
{

}

/*
 * Function:    hook_describe_cast_slow
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_slow(object caster, object *targets)
{
    int i;

    caster->catch_msg("You open your eyes.\n");
    tell_room(environment(caster), QCTNAME(caster) + " opens "+
        caster->query_possessive()+" eyes.\n", caster);
    for (i=0; i < sizeof(targets); i++)
    {
    	caster->catch_msg("You summon a slight fog that moves towards "+ 
    	    QTPNAME(targets[i]) +" direction. The fog surrounds " +
		    targets[i]->query_objective() + ", slowing "+
		    targets[i]->query_possessive() + " movement.\n");
	
	    targets[i]->catch_tell(caster->query_The_name(targets[i]) +" summons "+
	        "a slight fog that moves in your direction. The fog surrounds "+
	        "you.\n");
	
	    tell_room(environment(caster), QCTNAME(caster) +" summons a slight "+
	        "fog that moves in "+QTPNAME(targets[i])+" direction. The fog "+
	        "surrounds "+ targets[i]->query_objective() + ".\n",
	        ({ caster, targets[i] }), caster);
	}
}

/*
 * Function:    hook_slow_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_slow_resisted(object caster, object * targets)
{
    int i;

    for (i=0; i < sizeof(targets); i++)
    {
	    caster->catch_msg("You sense that " + QTNAME(targets[i]) + " is " +
		"not affected by your prayer.\n");
	    targets[i]->catch_msg("You shrug off " + QTPNAME(caster) +
		" prayer to slow you down.\n");
	}
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
    return "fragmos component (flameroot, black pearl shard)";
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
