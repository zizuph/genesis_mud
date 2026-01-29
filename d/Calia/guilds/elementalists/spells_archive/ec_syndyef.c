/*
 * Syndyasmos Earth + Earth combination spell the 
 * Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, June 2017
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
 * Function:    is_full_master_cleric_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_full_master_cleric_spell()
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
    set_spell_name("efotiagis");
    set_spell_desc("Syndyasmos Earth + Fire Combination");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_fail("Your prayer fails.\n");
    // Taxed as a 120%/130% CAID as it has a chance to damage or break armours
    // but only setting it to 100%/110% CAID for the actual damage 
    set_spell_combat_aid(110.0);
    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");    

    set_spell_element(SS_ELEMENT_EARTH, 50);
    set_spell_form(SS_FORM_CONJURATION, 50);
    
    // 2.0 times the standard cast time for a harm spell 
    set_spell_time_factor(2.0);
    
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
    if (TP->is_elemental_racial_cleric())
    {
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
    		result = 50.0;
    	else
    		result = 100.0;
    }
    else
    {
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
    		result = 45.4;
    	else
    		result = 90.9;
    }
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
    return ({ "_syndyasmos_component_" });
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_SYNDYASMOS)
    {
        return 0;
    }

    // Only full master clerics and higher get this spell
    if (!GUILD_MANAGER->query_is_full_master(player))
    {
        return 0;
    }

    // Only players who have finished the Guru quest get this spell
    if (!player->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
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
    
    if (caster->query_wiz_level())
    {
        // Wizards get all spells
        return 1;
    }
    
    // Only earth clerics get this spell
    if (GUILD_MANAGER->query_primary_element(caster) != "earth")
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
    
    if (!GUILD_MANAGER->query_current_syndyasmos_partner(caster))
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
    string caster_message, caster_name, watcher_message, partner_name;
    string partner_message;
    object partner_ob;
    
    caster_name = capitalize(caster->query_real_name());
    partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
    partner_ob = find_player(partner_name);
    partner_name = capitalize(partner_name);

    caster_message = "You hold out your hand and focus on gathering the "+
        "power of Lady Gu.\n"+partner_name+" holds out "+
        partner_ob->query_possessive()+ " and concentrates intensely.\n";
    partner_message = caster_name+" holds out "+caster->query_possessive()+
        " hand and concentrates intensely.\nYou hold out your hand and focus "+
        "on gathering the power of Lord Pyros.\n";
    watcher_message = QCTNAME(caster) + " and "+QTNAME(partner_ob)+
        " both hold out their hands and begin to concentrate intensely.\n";
        
    caster->catch_tell(caster_message);
    partner_ob->catch_tell(partner_message);
    tell_room(environment(caster), watcher_message, 
    	({ caster, partner_ob }), caster);
    
    setuid();
    seteuid(getuid());
    int conduit_penalty = caster->query_prop(CONDUIT_PENALTY);
    
    switch(conduit_penalty)
    {
    	case 1:  // halved conduit gain
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
		    caster->catch_tell("\n\nYou have acted outside of your Vow "+
		    	"of Service. "+
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
    string partner_message, partner_name, caster_name;
    object partner_ob;
    int phurt = result[0];
    string hitloc_desc = result[1];
    mixed * armour = target->query_armour(-1);
    
    partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
    partner_ob = find_player(partner_name);
    partner_name = capitalize(partner_name);    
        
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        caster_message = "The energy wave buzzes by " + QTNAME(target) + 
        	", missing "+target->query_objective()+" completely.\n";
        partner_message = "The energy wave buzzes by " + QTNAME(target) + 
        	", missing "+target->query_objective()+" completely.\n";
        target_message = "The energy wave buzzes by you, missing you "+
        	"completely.\n";
        watcher_message = "The energy wave buzzes by " + QTNAME(target) + 
        	", missing "+target->query_objective()+" completely.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0..5:
        	caster_message = "The energy wave barely hits " + QTNAME(target) +
        	    ", doing very minor damage to "+target->query_objective();
        	partner_message = "The energy wave barely hits " + QTNAME(target) +
        	    ", doing very minor damage to "+target->query_objective();
            target_message = "The energy wave barely hits you, doing very "+
                "minor damage to you";
            watcher_message = "The energy wave barely hits " + QTNAME(target) +
        	    ", doing very minor damage to "+target->query_objective();
            if (armour)
            {
            	caster_message += " and minor damage to "+
            		target->query_possessive()+
        	        " armours.\n";
        	    partner_message += " and minor damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	    target_message += " to you and minor damage to your armours.\n";
        	    watcher_message += " and minor damage to "+
        	    	target->query_possessive()+
                    " armours.\n";
                
                for(int i=0; i < sizeof(armour); i++)
                {
	                int magic_res = armour[i]->
                		query_magic_res(MAGIC_I_RES_MAGIC);
	                if (armour[i]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
		    	    {
		    	    	if (!magic_res)
			        		armour[i]->set_condition(
			        			armour[i]->query_condition() + random(1));
		        	}
		        	else
		        	{
		        		armour[i]->set_condition(
		        			armour[i]->query_condition() + 2);
		        		armour[i]->set_likely_break(
		        			armour[i]->query_likely_break() + 4);
		        	}
		        }
        	}
        	else
        	{
        		caster_message += ".\n";
        		partner_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";
        	}
        	        	    
            break;
                       
        case 6..15:
            caster_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing minor damage to "+target->query_objective();
        	partner_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing minor damage to "+target->query_objective();
            target_message = "The energy wave hits you, doing minor damage "+
                "to you";
            watcher_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing minor damage to "+target->query_objective();
            
            if (armour)
            {
            	caster_message += " and some damage to "+
            		target->query_possessive()+
        	        " armours.\n";
        	    partner_message += " and some damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	    target_message += " and some damage to your armours.\n";
        	    watcher_message += " and some damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	    
        	    for(int i=0; i < sizeof(armour); i++)
                {
		            int magic_res = armour[i]->
                		query_magic_res(MAGIC_I_RES_MAGIC);
		            if (armour[i]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
		            {
		            	if (!magic_res)
			            	armour[i]->set_condition(
			            		armour[i]->query_condition() + random(1) + 1);
			            else
			            	armour[i]->set_condition(
			            		armour[i]->query_condition() + random(1));
		            }
		            else
		            {
		            	armour[i]->set_condition(
		            		armour[i]->query_condition() + random(2) + 2);
		            	armour[i]->set_likely_break(
		            		armour[i]->query_likely_break() + random(2) + 4);
		            }
		        }
        	}
        	else
        	{
        		caster_message += ".\n";
        		partner_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}            
            	
            break;
            
        case 16..30:
            caster_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing significant damage to "+target->query_objective();
        	partner_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing significant damage to "+target->query_objective();        	    
            target_message = "The energy wave hits you, doing significant "+
                "damage to you";
            watcher_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing significant damage to "+target->query_objective();
            
            if (armour)
            {
            	caster_message += " and some damage to "+
            		target->query_possessive()+
        	        " armours.\n";
        	    partner_message += " and some damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	    target_message += " and some damage to your armours.\n";
        	    watcher_message += " and some damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	        
        	    for(int i=0; i < sizeof(armour); i++)
                {    
		            int magic_res = armour[i]->
                		query_magic_res(MAGIC_I_RES_MAGIC); 
		            if (armour[i]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
		            {
		            	if (!magic_res)
		            	{
			            	armour[i]->set_condition(
			            		armour[i]->query_condition() + random(1) + 1);
			            	armour[i]->set_likely_break(
			            		armour[i]->query_likely_break() + random(1));
			            }
			            else
			            {
			            	armour[i]->set_condition(
			            		armour[i]->query_condition() + random(1));
			            }
		            }
		            else
		            {
		            	armour[i]->set_condition(
		            		armour[i]->query_condition() + random(2) + 2);
		            	armour[i]->set_likely_break(
		            		armour[i]->query_likely_break() + random(3) + 5);
		            }
		        }
	        }
            else
        	{
        		caster_message += ".\n";
        		partner_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}	
            break;
       
        case 31..60:
            caster_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing major damage to "+target->query_objective();
        	partner_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing major damage to "+target->query_objective();        	    
            target_message = "The energy wave hits you, doing major "+
                "damage to you";
            watcher_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing major damage to "+target->query_objective(); 
            
            if (armour)
            {
            	caster_message += " and significant damage to "+
            		target->query_possessive()+
        	        " armours.\n";
        	    partner_message += " and significant damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	    target_message += " and significant damage to your armours.\n";
        	    watcher_message += " and significant damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
            	
            	for(int i=0; i < sizeof(armour); i++)
                {	
		            int magic_res = armour[i]->
                		query_magic_res(MAGIC_I_RES_MAGIC);
		            if (armour[i]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
		            {
		            	if (!magic_res)
		            	{
			            	armour[i]->set_condition(
			            		armour[i]->query_condition() + random(1) + 1);
			            	armour[i]->set_likely_break(
			            		armour[i]->query_likely_break() + random(1));
			            }
			            else
			            {
			            	armour[i]->set_condition(
			            		armour[i]->query_condition() + random(1));
			            	armour[i]->set_likely_break(
			            		armour[i]->query_likely_break() + random(1));
			            }
		            }
		            else
		            {
		            	armour[i]->set_condition(
		            		armour[i]->query_condition() + random(2) + 3);
		            	armour[i]->set_likely_break(
		            		armour[i]->query_likely_break() + random(4) + 6);
		            }
		        }
	        }
            else
        	{
        		caster_message += ".\n";
        		partner_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}
            break;
        
        case 61..90:
            caster_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing critical damage to "+target->query_objective();
        	partner_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing critical damage to "+target->query_objective();        	    
            target_message = "The energy wave hits you, doing critical "+
                "damage to you";
            watcher_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing critical damage to "+target->query_objective();
            
            if (armour)
            {
            	caster_message += " and significant damage to "+
            		target->query_possessive()+
    	        	" armours.\n";
        	    partner_message += " and significant damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	    target_message += " and significant damage to your armours.\n";
        	    watcher_message += " and significant damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	        
            	for(int i=0; i < sizeof(armour); i++)
                {	
		            if (armour[i]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
		            {
		            	armour[i]->set_condition(
		            		armour[i]->query_condition() + random(1) + 1);
		            	armour[i]->set_likely_break(
		            		armour[i]->query_likely_break() + random(1) + 1);
		            }
		            else
		            {
		            	armour[i]->set_condition(
		            		armour[i]->query_condition() + random(2) + 4);
		            	armour[i]->set_likely_break(
		            		armour[i]->query_likely_break() + random(4) + 8);
		            }
		        }
	        }
            else
        	{
        		caster_message += ".\n";
        		partner_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}
            break;
                
        case 91..99:
            caster_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing near-fatal damage to "+target->query_objective();
        	partner_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing near-fatal damage to "+target->query_objective();        	    
            target_message = "The energy wave hits you, doing near-fatal "+
                "damage to you";
            watcher_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing near-fatal damage to "+target->query_objective();
            
            if (armour)
            {
            	caster_message += " and significant damage to "+
            		target->query_possessive()+
    	        	" armours.\n";
        	    partner_message += " and significant damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	    target_message += " and significant damage to your armours.\n";
        	    watcher_message += " and significant damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	        
            	for(int i=0; i < sizeof(armour); i++)
                {	
		            int magic_res = armour[i]->
                		query_magic_res(MAGIC_I_RES_MAGIC);
		            if (armour[i]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
		            {
		            	if (!magic_res)
		            	{
			            	armour[i]->set_condition(
			            		armour[i]->query_condition() + random(1) + 2);
			            	armour[i]->set_likely_break(
			            		armour[i]->query_likely_break() + random(1) +
			            			2);
			            }
			            else
			            {
			            	armour[i]->set_condition(
			            		armour[i]->query_condition() + random(1) + 1);
			            	armour[i]->set_likely_break(
			            		armour[i]->query_likely_break() + random(1) +
			            			1);
			            }
		            }
		            else
		            {
		            	armour[i]->set_condition(
		            		armour[i]->query_condition() + random(2) + 5);
		            	armour[i]->set_likely_break(
		            		armour[i]->query_likely_break() + random(4) + 10);
		            }
		        }
	        }
            else
        	{
        		caster_message += ".\n";
        		partner_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}
            break;
        
        default:
            caster_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing fatal damage to "+target->query_objective();
        	partner_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing fatal damage to "+target->query_objective();        	    
            target_message = "The energy wave hits you, doing fatal "+
                "damage to you";
            watcher_message = "The energy wave hits " + QTNAME(target) +
        	    ", doing fatal damage to "+target->query_objective();
            
            if (armour)
            {
            	caster_message += " and major damage to "+
            		target->query_possessive()+
    	        	" armours.\n";
        	    partner_message += " and major damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	    target_message += " and major damage to your armours.\n";
        	    watcher_message += " and major damage to "+
        	    	target->query_possessive()+
        	        " armours.\n";
        	        
            	for(int i=0; i < sizeof(armour); i++)
                {	
		            if (armour[i]->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
		            {
		            	armour[i]->set_condition(
		            		armour[i]->query_condition() + random(1) + 3);
		            	armour[i]->set_likely_break(
		            		armour[i]->query_likely_break() + random(1) + 3);
		            }
		            else
		            {
		            	armour[i]->set_condition(
		            		armour[i]->query_condition() + random(2) + 6);
		            	armour[i]->set_likely_break(
		            		armour[i]->query_likely_break() + random(4) + 12);
		            }
		        }
	        }
            else
        	{
        		caster_message += ".\n";
        		partner_message += ".\n";
        	    target_message += ".\n";
        	    watcher_message += ".\n";        	    
        	}
            break;
        }
    }
        
    caster->catch_msg(caster_message);
    partner_ob->catch_msg(partner_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, 
    	({ caster, partner_ob, target }));
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
	 string caster_message, target_message, watcher_message;
	 string partner_message, partner_name, caster_name;
    object partner_ob;

    string go_plural;
    
    partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
    partner_ob = find_player(partner_name);
    partner_name = capitalize(partner_name);
    caster_name = capitalize(caster->query_real_name());

    if(sizeof(targets) > 1)
      go_plural = "them";
    else
      go_plural = targets[0]->query_objective();
      
    caster_message= "Your prayers being heard, you extend " +
		      "your hands towards "+ partner_name+" and as you "+
		      "do so, a wave of earthy energy rushes towards "+
		      partner_ob->query_objective()+".\n"+
		      partner_name+" extends "+partner_ob->query_possessive()+
		      " hands towards you and as "+partner_ob->query_pronoun()+
		      " does so, a wave of fiery energy rushes towards you.\n"+
		      "The two energy waves collide between you and begin to "+
		      "mesh and mingle by twisting into one another. Suddenly "+
		      "the now combined energy wave turns and rushes towards "+
		      COMPOSITE_LIVE(targets) +"\n";
	partner_message= "Your prayers being heard, you extend " +
		      "your hands towards "+ caster_name+" and as you "+
		      "do so, a wave of fiery energy rushes towards "+
		      caster->query_objective()+".\n"+
		      caster_name+" extends "+caster->query_possessive()+
		      " hands towards you and as "+caster->query_pronoun()+
		      " does so, a wave of earthly energy rushes towards you.\n"+
		      "The two energy waves collide between you and begin to "+
		      "mesh and mingle by twisting into one another. Suddenly "+
		      "the now combined energy wave turns and rushes towards "+
		      COMPOSITE_LIVE(targets) +"\n";	      
    target_message = QCTNAME(caster) + " extends " + 
    		  caster->query_possessive() +
			  " hands towards "+partner_ob->query_the_name(targets)+" and as "+
			  caster->query_pronoun()+" does so, a wave of earthly energy "+
			  "rushes "+
			  "towards "+partner_ob->query_objective()+".\n"+
			  partner_ob->query_The_name(targets)+" extends "+
			  	partner_ob->query_possessive()+
			  " hands towards "+caster->query_the_name(targets)+" and as "+
			  partner_ob->query_pronoun()+" does so, a wave of fiery energy "+
			  "shoots "+
			  "towards "+caster->query_objective()+".\nThe two energy waves "+
			  "collide between them and begin to mesh and mingle by twisting "+
			  "into one another. Suddenly the now combined energy wave turns "+
			  "and rushes towards you!\n";
    watcher_message = QCTNAME(caster) + " extends " + 
    		  caster->query_possessive() +
			  " hands towards "+QTNAME(partner_ob)+" and as "+
			  caster->query_pronoun()+" does so, a wave of earthly energy "+
			  "rushes "+
			  "towards "+partner_ob->query_objective()+".\n"+
			  QCTNAME(partner_ob)+" extends "+partner_ob->query_possessive()+
			  " hands towards "+QTNAME(caster)+" and as "+
			  partner_ob->query_pronoun()+" does so, a wave of fiery energy "+
			  "shoots "+
			  "towards "+caster->query_objective()+".\nThe two energy waves "+
			  "collide between them and begin to mesh and mingle by twisting "+
			  "into one another. Suddenly the now combined energy wave turns "+
			  "and rushes towards " + COMPOSITE_LIVE(targets) +".\n";
	
	caster->catch_msg(caster_message);
    partner_ob->catch_msg(partner_message);
    targets->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, 
    	({ caster, partner_ob }) + targets);
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
        + "the manifestation of syndyasmos.\n");
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
    return "blade, alexandrite shard";
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
