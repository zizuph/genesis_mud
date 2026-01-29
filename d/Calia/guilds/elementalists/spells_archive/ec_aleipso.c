/*
 * Self Healing Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, January 2017
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/heal";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

public float actual_caid;
public string branch;

/*
 * Function:    is_child_cleric_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_child_cleric_spell()
{
    return 1;
}

/*
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_heal_spell()
{
    set_spell_name("aleipso");
    set_spell_desc("Heal");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_HARD);    
    set_spell_combat_aid(175.0);
    set_spell_time_factor(1.5);

    set_spell_target(spell_target_one_present_living);

    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
    
    set_spell_element(SS_ELEMENT_WATER, 20);
    set_spell_form(SS_FORM_ABJURATION, 25);
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
    string primary_element;
    string caster = TP->query_real_name();
    
    
    // Are they a child cleric? If so, it's 55 CAID.
    if (GUILD_MANAGER->query_is_child_cleric(caster))
    {
    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
    	{
    		result = 15.7;
    		actual_caid = 27.5;
    	}
    	else
    	{
    		result = 31.4;
    		actual_caid = 55.0;
    	}
    	branch = "child";
        return result;
    }
    
    // What is their primary element?
    primary_element = GUILD_MANAGER->query_primary_element(caster);
    
    switch(primary_element)
    {
        case "fire":
        // Has guru quest been completed? If so, set at 80, otherwise 60
        if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
        {
        	if (TP->query_prop(CONDUIT_PENALTY) == 3)
        	{
        		result = 22.8;
        		actual_caid = 40.0;
        	}
        	else
        	{
            	result = 45.7;
            	actual_caid = 80.0;
            }
            branch = "fire";
            return result;
            break;
        }
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
        {
        	result = 17.1;
        	actual_caid = 30.0;
        }
        else
        {
        	result = 34.3;
        	actual_caid = 60.0;
        }
        branch = "fire";
        return result;
        break;
    
    case "earth":
        // Has guru quest been completed? If so, set at 110, otherwise 90
        if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
        {
        	if (TP->query_prop(CONDUIT_PENALTY) == 3)
        	{
        		result = 30.0;
        		actual_caid = 52.5;
        	}
        	else
        	{
            	result = 60.0;
            	actual_caid = 105.0;
            }
            branch = "earth";
            return result;
            break;
        }
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
        {
        	result = 25.7;
        	actual_caid = 45.0;
        }
        else
        {
        	result = 51.4;
        	actual_caid = 90.0;
        }
        branch = "earth";
        return result;
        break;
    
    case "water":
        // Has guru quest been completed? If so, set at 140, otherwise 120
        if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
        {
        	if (TP->query_prop(CONDUIT_PENALTY) == 3)
        	{
        		result = 50.0;
        		actual_caid = 87.5;
        	}
        	else
        	{
            	result = 100.0;
            	actual_caid = 175.0;
            }
            branch = "water";
            return result;
            break;
        }
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
        {
        	result = 40.0;
        	actual_caid = 70.0;
        }
        else
        {
        	result = 80.0;
        	actual_caid = 140.0;
        }
        branch = "water";
        return result;
        break;
    
    case "air":
        // Has guru quest been completed? If so, set at 90, otherwise 70
        if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
        {
        	if (TP->query_prop(CONDUIT_PENALTY) == 3)
        	{
        		result = 25.7;
        		actual_caid = 45.0;
        	}
        	else
        	{
            	result = 51.4;
            	actual_caid = 90.0;
            }
            branch = "air";
            return result;
            break;
        }
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
        {
        	result = 20.0;
        	actual_caid = 35.0;
        }
        else
        {
        	result = 40.0;
        	actual_caid = 70.0;
        }
        branch = "air";
        return result;
        break;
        
    case "life":
        // Has guru quest been completed? If so, set at 100, otherwise 70
        if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
        {
        	if (TP->query_prop(CONDUIT_PENALTY) == 3)
        	{
        		result = 31.4;
        		actual_caid = 55.0;
        	}
        	else
        	{
            	result = 62.9;
            	actual_caid = 110.0;
            }
            branch = "spirit";
            return result;
            break;
        }
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
        {
        	result = 28.5;
        	actual_caid = 50.0;
        }
        else
        {
        	result = 57.1;
        	actual_caid = 100.0;
        }
        branch = "spirit";
        return result;
        break;
    }
        
    
    // If all else fails, give the lowest heal CAID
    if (TP->query_prop(CONDUIT_PENALTY) == 3)
    {
    	result = 15.7;
    	actual_caid = 27.5;
    }
    else
    {
    	result = 31.4;
    	actual_caid = 55.0;
    }
    branch = "unknown";
    return result;
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    string caster = TP->query_real_name();
    string element = GUILD_MANAGER->query_primary_element(caster);
    
    if (GUILD_MANAGER->query_is_child_cleric(caster))
        return ({  });
    else
    {
        switch(element)
        {
            case "fire":
                return ({ "_fire_component_" });
                break;
            
            case "air":
                return ({ "_air_component_" });
                break;
                
            case "water":
                return ({  });
                break;
            
            case "earth":
                return ({ "_earth_component_" });
                break;
                
            case "life":
                return ({  });
                break;
        }
    }
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_ALEIPSO)
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
        caster_message = "You hold out your palm with the fingers pointed "
            + "away from you and focus on gathering the power of the "
            + "moisture in the air as you seek Lord Diabrecho's succor.\n";
        watcher_message = QCTNAME(caster) + " holds out "
            + caster->query_possessive() + " palm and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You summon your inner reserves of power and "
            + "focus your mind on utilizing the element of water.\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and concentrates.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
    int conduit_penalty = caster->query_prop(CONDUIT_PENALTY);
    
    // Child Cleric Conduit
    if (GUILD_MANAGER->query_is_child_cleric(caster))
    {
    	switch(conduit_penalty)
	    {
	    	case 1:  // halved conduit gain
	    		GUILD_MANAGER->add_practice_level(caster, 1);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
			    GUILD_MANAGER->add_guild_conduit(1);
			    caster->catch_tell("\n\nYou have acted outside of your Vow "+
			        "of Service. This strains your connection with the "+
			        "Circle and the Conduit.\n\n\n");
	    		break;
	    	case 2:  // halved conduit gain, double conduit cost
	    		GUILD_MANAGER->add_practice_level(caster, 1);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
			    GUILD_MANAGER->add_guild_conduit(1);
			    caster->catch_tell("\n\nYou have deliberately violated your "+
			        "Vow of Service. The Conduit between the Circle and the "+
			        "Five suffers from your lack of Faith.\n\n\n");
	    		break;
	    	case 3:  // halved conduit gain, double conduit cost, halved CAID
	    		GUILD_MANAGER->add_practice_level(caster, 1);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
			    GUILD_MANAGER->add_guild_conduit(1);
			    caster->catch_tell("\n\nYou have repeatedly violated your "+
			        "Vow of Service. With such malpractice, your prayers "+
			        "sound weak and hollow.\n\n\n");
	    		break;
	    	default:
	    		GUILD_MANAGER->add_practice_level(caster, 2);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
			    GUILD_MANAGER->add_guild_conduit(2);
	    		break;
	    }
    }
    
    // Master Cleric Conduit
    if (GUILD_MANAGER->query_is_master_cleric(caster))
    {
        // Master Guru Cleric Conduit
        if (caster->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
        {
        	switch(conduit_penalty)
		    {
		    	case 1:  // halved conduit gain
		    		GUILD_MANAGER->add_practice_level(caster, 5);
				    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
				    GUILD_MANAGER->add_guild_conduit(5);
				    caster->catch_tell("\n\nYou have acted outside of your "+
				        "Vow of Service. This strains your connection with "+
				        "the Circle and the Conduit.\n\n\n");
		    		break;
		    	case 2:  // halved conduit gain, double conduit cost
		    		GUILD_MANAGER->add_practice_level(caster, 5);
				    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
				    GUILD_MANAGER->add_guild_conduit(5);
				    caster->catch_tell("\n\nYou have deliberately violated "+
				        "your Vow of Service. The Conduit between the Circle "+
				        "and the Five suffers from your lack of Faith.\n\n\n");
		    		break;
		    	case 3:  // halved conduit gain, double conduit cost, halved 
		    		     // CAID
		    		GUILD_MANAGER->add_practice_level(caster, 5);
				    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
				    GUILD_MANAGER->add_guild_conduit(5);
				    caster->catch_tell("\n\nYou have repeatedly violated "+
				        "your Vow of Service. With such malpractice, your "+
				        "prayers sound weak and hollow.\n\n\n");
		    		break;
		    	default:
		    		GUILD_MANAGER->add_practice_level(caster, 10);
				    GUILD_MANAGER->add_player_conduit_earned(caster, 10);
				    GUILD_MANAGER->add_guild_conduit(10);
		    		break;
		    }
        }
        else
        {
            switch(conduit_penalty)
		    {
		    	case 1:  // halved conduit gain
		    		GUILD_MANAGER->add_practice_level(caster, 2);
				    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
				    GUILD_MANAGER->add_guild_conduit(2);
				    caster->catch_tell("\n\nYou have acted outside of your "+
				        "Vow of Service. This strains your connection with "+
				        "the Circle and the Conduit.\n\n\n");
		    		break;
		    	case 2:  // halved conduit gain, double conduit cost
		    		GUILD_MANAGER->add_practice_level(caster, 2);
				    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
				    GUILD_MANAGER->add_guild_conduit(2);
				    caster->catch_tell("\n\nYou have deliberately violated "+
				        "your Vow of Service. The Conduit between the Circle "+
				        "and the Five suffers from your lack of Faith.\n\n\n");
		    		break;
		    	case 3:  // halved conduit gain, double conduit cost, halved 
		    		     // CAID
		    		GUILD_MANAGER->add_practice_level(caster, 2);
				    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
				    GUILD_MANAGER->add_guild_conduit(2);
				    caster->catch_tell("\n\nYou have repeatedly violated "+
				        "your Vow of Service. With such malpractice, your "+
				        "prayers sound weak and hollow.\n\n\n");
		    		break;
		    	default:
		    		GUILD_MANAGER->add_practice_level(caster, 5);
				    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
				    GUILD_MANAGER->add_guild_conduit(5);
		    		break;
		    }
        }
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_heal_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_heal_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: hook_describe_heal_cast
 * Description:   Describe casting of the spell. This takes place before the
 *                actual healing happens.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 */
public void
hook_describe_heal_cast(object caster, object *targets)
{
    if (IN_ARRAY(caster, targets))
    {
        object * other_targets = targets - ({ caster });
        if (sizeof(other_targets))
        {
            caster->catch_tell("Moisture in the air coalesces into "
                + "thin streams of water that direct themselves to "
                + COMPOSITE_LIVE(other_targets) + " and yourself and "
                + "covers up your injuries.\n");
        }
        else
        {
            caster->catch_tell("Moisture in the air coalesces into "
                + "thin streams of water that direct themselves to your "
                + "injuries.\n");
        }
    }
    else
    {
        caster->catch_tell("Moisture in the air coalesces into thin "
            + "streams of water that direct themselves to "
            + COMPOSITE_LIVE(targets) + " and covers up their "
            + "injuries.\n");
    }
}

/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        switch (heal_amounts[index])
        {
        case 0:
            tell_room(environment(caster), QCTNAME(target)
                + " doesn't look any healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body, but does not make you "
                + "any healthier.\n");
            break;
        
        case 1..100:
            tell_room(environment(caster), QCTNAME(target)
                + " looks healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body and closes a few of your "
                + "wounds.\n");
            break;
            
        case 101..250:
            tell_room(environment(caster), QCTNAME(target)
                + " looks healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body and closes quite a few of your "
                + "wounds.\n");
            break;
        
        case 251..500:
            tell_room(environment(caster), QCTNAME(target)
                + " looks healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body and closes many of your "
                + "wounds.\n");
            break;

        default:
            tell_room(environment(caster), QCTNAME(target)
                + " looks healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body, closes your wounds, and "
                + "makes you a lot healthier.\n");
            break;            
        }
     
    int a_actual_caid = ftoi(actual_caid);
    send_debug_message("heal_spell", caster->query_name() +
        "(" + branch + " branch) CAID: " + a_actual_caid + "\n");
        
    }
}


/*
 * Function name: hook_describe_harm_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * harm_amounts - the amounts healed
 */
public void
hook_describe_harm_result(object caster, object *targets, int * harm_amounts)
{
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        switch (harm_amounts[index])
        {
        case 0:
            tell_room(environment(caster), QCTNAME(target)
                + " doesn't look phased by the living energy.\n", targets);
            target->catch_tell("Living energies enter your body, but "
                + "you are unphazed.\n");
            break;
        
        case 1..100:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the living energies.\n", targets);
            target->catch_tell("Living energies enter your body, and "
                + "hurt you slightly.\n");
            break;
            
        case 101..250:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the living energies.\n", targets);
            target->catch_tell("Living energies enter your body, and "
                + "hurt you somewhat.\n");
            break;
        
        case 251..500:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the living energies.\n", targets);
            target->catch_tell("Living energies enter your body, and "
                + "hurt you moderately.\n");
            break;

        default:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the living energies.\n", targets);
            target->catch_tell("Living energies enter your body, and "
                + "hurt you greatly.\n");
            break;
        }
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
    write("You need a proper ritual component as part of "
        + "the prayer of " + query_spell_name() + " to Lord "
        + "Diabrecho.\n");
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
    
    if (GUILD_MANAGER->query_is_child_cleric(caster))
        return "none";
    else
    {
        switch(element)
        {
            case "fire":
                return "fire component (fireweed, golden pyrite shard)";
                break;
            
            case "air":
                return "air component (chicory, blue topaz shard)";
                break;
                
            case "water":
                return "none";
                break;
            
            case "earth":
                return "earth component (cladina, jade shard)";
                break;
                
            case "life":
                return "none";
                break;
        }
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
