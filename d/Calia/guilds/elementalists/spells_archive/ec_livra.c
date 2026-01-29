/*
 * Damage Armour/Pound Body Spell 
 * for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, February 2017
 */

#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/harm";
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
 * Function:    config_harm_spell
 * Description: Config function for harm damage spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_harm_spell()
{
    set_spell_name("livra");
    set_spell_desc("Pound body/Damage armour");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    // Taxed as a 60% CAID as it has a chance to damage or break armours
    // but only setting it to 50% CAID for the actual damage 
    set_spell_combat_aid(50.0);
    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");    

    set_spell_element(SS_ELEMENT_EARTH, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
    
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_EARTH)); 
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
    
    if (TP->query_prop(CONDUIT_PENALTY) == 3)
		result = 50.0;
	else
		result = 100.0;
    return result;
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({  });
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_LIVRA)
    {
        return 0;
    }

    // Only master clerics and higher get this spell
    if (GUILD_MANAGER->query_is_child_cleric(player))
    {
        return 0;
    }
    
    // Only earth clerics get this spell
    if (GUILD_MANAGER->query_primary_element(player) != "earth")
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
    
    return 1;
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTPNAME(target) + " armour is already being "+
            "damaged by a livra prayer!\n");
    }
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
    caster_message = "You focus your attention and prepare "+
            "to strike.\n";
    watcher_message = QCTNAME(caster) + " beings to concentrate intensely.\n";
        
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
		    caster->catch_tell("\n\nYou have acted outside of your Vow "+
		        "of Service. "+
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
		    caster->catch_tell("\n\nYou have repeatedly violated your Vow "+
		        "of Service. "+
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
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from harm's hit_me.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];
    object armour = target->query_armour(A_BODY);
    int magic_res = armour->query_magic_res(MAGIC_I_RES_MAGIC);    
        
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        caster_message = "You strike at " + QTNAME(target) + 
        	" with your rocklike fists but miss completely.\n";
        target_message = QCTNAME(caster)+" strikes at you with "+
            caster->query_possessive()+" rocklike fists but misses "+
            "you completely.\n";
        watcher_message = QCTNAME(caster)+ " strikes at " + QTNAME(target) +
            " with " + caster->query_possessive() + " rocklike fists "+
            "but misses " +
            target->query_objective() + " completely.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0..5:
        	caster_message = "You strike at " + QTNAME(target) +
        	    " with your rocklike fists but barely hit "+
        	    target->query_objective()+", doing "+
        	    "very minor damage to "+target->query_objective();
            target_message = QCTNAME(caster)+" strikes at you with "+
            	caster->query_possessive()+" rocklike fists but barely "+
            	"hits you for very minor damage";
            watcher_message = QCTNAME(caster)+" strikes at " + QTNAME(target)+
            	" with " + caster->query_possessive()+" rocklike fists "+
            	"but barely "+
            	"hits "+target->query_objective()+ ".\n";
            if (armour)
            {
            	caster_message += " and minor damage to "+
            	target->query_possessive()+
        	        " "+armour->query_short()+".\n";
        	    target_message += " to you and minor damage to your "+
        	    	armour->query_short() + ".\n";
        	    watcher_message += " and minor damage to "+
        	    	target->query_possessive()+
                    " "+armour->query_short()+".\n";
                    
	    	    if (armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
	    	    {
	    	    	if (magic_res)
		        		armour->set_condition(armour->query_condition() + 
		        			random(1));
		        }
	        	else
	        	{
	        		armour->set_condition(armour->query_condition() + 2);
	        		armour->set_likely_break(armour->query_likely_break() + 4);
	        	}
        	}
        	else
        	{
        		caster_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";
        	}
        	        	    
            break;
                       
        case 6..15:
            caster_message = "You strike at " + QTNAME(target) +
        	    " with your rocklike fists and hit "+
        	    target->query_objective()+", doing "+
        	    "only minor damage to "+target->query_objective();
            target_message = QCTNAME(caster)+" strikes at you with "+
            	caster->query_possessive()+" rocklike fists and "+
            	"hits you doing minor damage";
            watcher_message = QCTNAME(caster)+" strikes at " + QTNAME(target) +
            	" with " + caster->query_possessive()+" rocklike fists and "+
            	"hits "+target->query_objective()+ " doing minor damage to "+
            	target->query_objective();
            
            if (armour)
            {
            	caster_message += " and some damage to "+
            	    target->query_possessive()+
        	        " "+armour->query_short()+".\n";
        	    target_message += " to you and some damage to your "+
        	        armour->query_short() + ".\n";
        	    watcher_message += " and some damage to "+
        	        target->query_possessive()+
            		" "+armour->query_short()+".\n";
	            if (armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
	            {
	            	if (!magic_res)
		            	armour->set_condition(armour->query_condition() +
		            		random(1) + 1);
		            else
		            	armour->set_condition(armour->query_condition() +
		            		random(1));
		        }
	            else
	            {
	            	armour->set_condition(armour->query_condition() + 
	            	    random(2) + 2);
	            	armour->set_likely_break(armour->query_likely_break()+
	            	    random(2) + 4);
	            }
        	}
        	else
        	{
        		caster_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}            
            	
            break;
            
        case 16..30:
            caster_message = "You strike at " + QTNAME(target) +
        	    " with your rocklike fists and hit "+
        	    target->query_objective()+", doing "+
        	    "significant damage to "+target->query_objective();        	    
            target_message = QCTNAME(caster)+" strikes at you with "+
            	caster->query_possessive()+" rocklike fists and "+
            	"hits you doing significant damage";
            watcher_message = QCTNAME(caster)+" strikes at " + QTNAME(target) +
            	" with " + caster->query_possessive()+" rocklike fists and "+
            	"hits "+target->query_objective()+ " doing significant "+
            	"damage to "+
            	target->query_objective();
            
            if (armour)
            {
            	caster_message += " and some damage to "+
            	    target->query_possessive()+
        	        " "+armour->query_short()+".\n";
        	    target_message += " to you and some damage to your "+
        	        armour->query_short()+
        	        ".\n";
        	    watcher_message += " and some damage to "+
        	        target->query_possessive()+
            		" "+armour->query_short()+".\n";
	            if (armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
	            {
	            	if (!magic_res)
	            	{
		            	armour->set_condition(armour->query_condition() +
		            	    random(1) + 1);
		            	armour->set_likely_break(armour->query_likely_break() +
		            	    random(1));
		            }
		            else
		            {
		            	armour->set_condition(armour->query_condition() +
		            	    random(1));
		            }
	            }
	            else
	            {
	            	armour->set_condition(armour->query_condition() + 
	            	    random(2) + 2);
	            	armour->set_likely_break(armour->query_likely_break() + 
	            	    random(3) + 5);
	            }
	        }
            else
        	{
        		caster_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}	
            break;
       
        case 31..60:
            caster_message = "You strike at " + QTNAME(target) +
        	    " with your rocklike fists and hit "+
        	    target->query_objective()+", doing "+
        	    "major damage to "+target->query_objective();        	    
            target_message = QCTNAME(caster)+" strikes at you with "+
            	caster->query_possessive()+" rocklike fists and "+
            	"hits you doing major damage"; 
            watcher_message = QCTNAME(caster)+" strikes at " + QTNAME(target) +
            	" with " + caster->query_possessive()+" rocklike fists and "+
            	"hits "+target->query_objective()+ " doing major damage to "+
            	target->query_objective(); 
            
            if (armour)
            {
            	caster_message += " and significant damage to "+
            	    target->query_possessive()+
        	    	" "+armour->query_short()+".\n";
        	    target_message += " to you and significant damage to your "+
        	    	armour->query_short()+".\n";
        	    watcher_message += " and significant damage to "+
        	        target->query_possessive()+
            		" "+armour->query_short()+".\n";
            		
	            if (armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
	            {
	            	if (!magic_res)
	            	{
		            	armour->set_condition(armour->query_condition() +
		            	    random(1) + 1);
		            	armour->set_likely_break(armour->query_likely_break() +
		            	    random(1));
		            }
		            else
		            {
		            	armour->set_condition(armour->query_condition() +
		            	    random(1));
		            	armour->set_likely_break(armour->query_likely_break() +
		            	    random(1));
		            }
	            }
	            else
	            {
	            	armour->set_condition(armour->query_condition() + 
	            	    random(2) + 3);
	            	armour->set_likely_break(armour->query_likely_break() + 
	            	    random(4) + 6);
	            }
	        }
            else
        	{
        		caster_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}
            break;
        
        case 61..90:
            caster_message = "You strike at " + QTNAME(target) +
        	    " with your rocklike fists and hit "+
        	    target->query_objective()+", doing "+
        	    "critical damage to "+target->query_objective();        	    
            target_message = QCTNAME(caster)+" strikes at you with "+
            	caster->query_possessive()+" rocklike fists and "+
            	"hits you doing critical damage"; 
            watcher_message = QCTNAME(caster)+" strikes at " + QTNAME(target) +
            	" with " + caster->query_possessive()+" rocklike fists and "+
            	"hits "+target->query_objective()+ " doing critical damage "+
            	"to "+
            	target->query_objective();
            
            if (armour)
            {
            	if (armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
            	{
            		caster_message += " and significant damage to "+
            		    target->query_possessive()+
        	    	    " "+armour->query_short()+".\n";
	        	    target_message += " to you and significant damage to "+
	        	        "your "+
	        	    	armour->query_short()+".\n";
	        	    watcher_message += " and significant damage to "+
	        	        target->query_possessive()+
	            		" "+armour->query_short()+".\n";
	            }
	            else
	            {
	            	caster_message += " and breaking "+
	            	    target->query_possessive()+
	        	    	" "+armour->query_short()+".\n";
	        	    target_message += " to you and breaking your "+
	        	    	armour->query_short()+".\n";
	        	    watcher_message += " and breaking "+
	        	        target->query_possessive()+
	            		" "+armour->query_short()+".\n";
	            	armour->remove_broken();
	            }
	        }
            else
        	{
        		caster_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}
            break;
                
        case 91..99:
            caster_message = "You strike at " + QTNAME(target) +
        	    " with your rocklike fists and hit "+
        	    target->query_objective()+", doing "+
        	    "near-fatal damage to "+target->query_objective();        	    
            target_message = QCTNAME(caster)+" strikes at you with "+
            	caster->query_possessive()+" rocklike fists and "+
            	"hits you doing near-fatal damage";
            watcher_message = QCTNAME(caster)+" strikes at " + QTNAME(target) +
            	" with " + caster->query_possessive()+" rocklike fists and "+
            	"hits "+target->query_objective()+ " doing near-fatal damage "+
            	"to "+
            	target->query_objective();
            
            if (armour)
            {
            	if (armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
            	{
            		caster_message += " and significant damage to "+
            		    target->query_possessive()+
        	    		" "+armour->query_short()+".\n";
	        	    target_message += " to you and significant damage to "+
	        	    	"your "+
	        	    	armour->query_short()+".\n";
	        	    watcher_message += " and significant damage to "+
	        	    	target->query_possessive()+
	            		" "+armour->query_short()+".\n";
	            	if (!magic_res)
	            	{
		            	armour->set_condition(armour->query_condition() + 
		            		random(1) + 2);
		            	armour->set_likely_break(armour->query_likely_break() + 
		            		random(1) + 2);
		            }
		            else
		            {
		            	armour->set_condition(armour->query_condition() + 
		            		random(1) + 1);
		            	armour->set_likely_break(armour->query_likely_break() + 
		            		random(1) + 1);
		            }
	            }
	            else
	            {
	            	caster_message += " and breaking "+
	            		target->query_possessive()+
	        	    	" "+armour->query_short()+".\n";
	        	    target_message += " to you and breaking your "+
	        	    	armour->query_short()+".\n";
	        	    watcher_message += " and breaking "+
	        	    	target->query_possessive()+
	            		" "+armour->query_short()+".\n";
	            	armour->remove_broken();
	            }
            }
            else
        	{
        		caster_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}
            break;
        
        default:
            caster_message = "You strike at " + QTNAME(target) +
        	    " with your rocklike fists and hit "+
        	    target->query_objective()+", doing "+
        	    "fatal damage to "+target->query_objective();        	    
            target_message = QCTNAME(caster)+" strikes at you with "+
            	caster->query_possessive()+" rocklike fists and "+
            	"hits you doing fatal damage";
            watcher_message = QCTNAME(caster)+" strikes at " + QTNAME(target)+
            	" with " + caster->query_possessive()+" rocklike fists and "+
            	"hits "+target->query_objective()+ " doing fatal damage to "+
            	target->query_objective();
            
            if (armour)
            {
            	if (armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
            	{
            		caster_message += " and significant damage to "+
            			target->query_possessive()+
        	    		" "+armour->query_short()+".\n";
	        	    target_message += " to you and significant damage to "+
	        	    	"your "+
	        	    	armour->query_short()+".\n";
	        	    watcher_message += " and significant damage to "+
	        	    	target->query_possessive()+
	            		" "+armour->query_short()+".\n";
	            	armour->set_condition(armour->query_condition() + 
	            		random(1) + 2);
	            	armour->set_likely_break(armour->query_likely_break() + 
	            		random(1) + 2);
	            }
	            else
	            {
	            	caster_message += " and breaking "+
	            		target->query_possessive()+
	        	    	" "+armour->query_short()+".\n";
	        	    target_message += " to you and breaking your "+
	        	    	armour->query_short()+".\n";
	        	    watcher_message += " and breaking "+
	        	    	target->query_possessive()+
	            		" "+armour->query_short()+".\n";
	            	armour->remove_broken();
	            }
            }
            else
        	{
        		caster_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}
            break;
        }
    }
        
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object * targets)
{
	int i;
	
    string caster_message, target_message, watcher_message;
    
    caster_message = "You lunge towards " 
        + COMPOSITE_LIVE(targets) + " with a powerful strike.\n";
    target_message = QCTNAME(caster) + " lunges forward towards "+
        "you with a powerful strike.\n";
    watcher_message = QCTNAME(caster) + " lunges forward in a "+
    "powerful strike.\n";
   
    caster->catch_msg(caster_message);
    for (i=0;i < sizeof(targets); i++)
    {
    	targets[i]->catch_msg(target_message);
    }
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);    
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
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
    write("You need a proper ritual component to generate "
        + "the manifestation of " + query_spell_name() + ".\n");
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
