/*
 * Detect Alignment/Killer Spell for the Elemental Cleric Guild of Calia
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

inherit "/d/Genesis/specials/std/spells/alignment";
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
 * Function:    config_detect_resistance_spell
 * Description: Config function for detect_resistance spells. Redefine this in 
 *              your
 *              own detect_resistance spells to override the defaults.
 */
public void
config_alignment_spell()
{
    set_spell_name("seira");
    set_spell_desc("Detect alignment/killer");

    set_spell_element(SS_ELEMENT_FIRE, 30);
    set_spell_form(SS_FORM_DIVINATION, 30);

    // Needs to be particularly easy to cast to break through some resistances
    set_spell_task(TASK_SIMPLE);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_target(spell_target_present_objects);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_SEIRA)
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
    
    // Only fire clerics get this spell
    if (GUILD_MANAGER->query_primary_element(player) != "fire")
    {
        return 0;
    }    

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
    object target = targets[0];
    
    if (!targets[0]->query_prop(CORPSE_S_RACE))
    {
        caster_message = "You pray to Lord Pyros while gesturing towards " + 
            QTNAME(target) +".\n";
        watcher_message = QCTNAME(caster) + " gestures mysteriously " + 
              "while concentrating.\n";
    }
    else
    {
        caster_message = "You pray to Lord Pyros while gesturing towards " + 
            "the " + target->short() +".\n";
        watcher_message = QCTNAME(caster) + " gestures mysteriously towards "+ 
              "the " + target->short() + " while concentrating.\n";
    }
        
    caster->catch_msg(caster_message);
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

/*
 * Function:    hook_detect_resistance_cast
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_alignment_cast(object caster)
{
}

/*
 * Function:    hook_detect_resistance_resisted
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_alignment_resisted(object caster, object target, int resistance)
{
    if (!target->query_prop(CORPSE_S_RACE))
        caster->catch_msg(QCTNAME(target) + " resists your attempt to divine "
            + "any information.\n");
    else
        caster->catch_msg("The "+ target->short() + " resists your attempt "+
        	"to divine "
            + "any information.\n");
}

/*
 * Function name : hook_report_alignment
 * Description   : Hook method to be masked to provide your own descriptions
 *                 of the alignment.
 *
 * Arguments  : object caster        - The caster of the spell.
 *            : object target        - The target of the spell, who to check the alignment for.
 *            : int target_alignment - The alignment of the target.
 *            : int result           - Result of the spell cast, how well it was cast.
 */
public void
hook_report_alignment(object caster, object target, int target_alignment, int result)
{ 
    string align, killer;
    
    if (!target->query_prop(CORPSE_S_RACE))
    {
        switch(target_alignment)
        {
            case -1200..-600:
                align = "very evil";
                break;
                
            case -599..-100:
                align = "evil";
                break;
            
            case -99..99:
                align = "neutral";
                break;
            
            case 100..599:
                align = "good";
                break;
                        
            case 600..1200:
                align = "very good";
                break;
        }
        
        caster->catch_msg(QCTNAME(target)+ " appears to be " + align + ".\n");   
    }
    
    else
    {
        killer = capitalize(target->query_prop(CORPSE_AS_KILLER)[0]);
        caster->catch_tell("You divine that the " +target->short()+ " was "+
            "slain by " + killer + ".\n");
    }
    setuid();
    seteuid(getuid());
    GUILD_MANAGER->add_practice_level(caster, 10);
    GUILD_MANAGER->add_player_conduit_earned(caster, 10);
    GUILD_MANAGER->add_guild_conduit(10);    
}

/*
 * Function:    query_detect_resistance_ingredients
 * Description: This function defines what components are required for 
 *              this detect_resistance spell.
 */
public string *
query_alignment_ingredients(object caster)
{

    return ({ "_seira_component_" });
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
    return "seira component (eye, ruby shard)";
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
