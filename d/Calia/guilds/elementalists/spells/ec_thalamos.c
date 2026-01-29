/*
 * Stoneskin vs Undead Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Arman, April 2022
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <formulas.h>
#include <wa_types.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "stoneskin";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

#define MAX_CAID  (BASE_THALAMOS_AID + SCHIRMO_AID + DYNAMI_AID + EVIMERO_AID)

#define DEBUG(x)  find_player("arman")->catch_msg("[ec_thalamos] " + x + "\n")


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
 * Function:    config_stoneskin_spell
 * Description: Config function for stoneskin spells. Redefine this in your
 *              own stoneskin spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_stoneskin_spell()
{
    set_spell_name("thalamos");
    set_spell_desc("Undead ward");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_stationary(0);

    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
    set_spell_combat_aid(MAX_CAID);
    set_spell_element(SS_ELEMENT_LIFE, 50);
    set_spell_form(SS_FORM_ABJURATION, 50);
    set_spell_task(TASK_ROUTINE);    

    // Can only cast stoneskin on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "thalamos_obj");

}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float result = 100.0;
    int penalty = TP->query_prop(CONDUIT_PENALTY);
    
    switch(penalty)
    {
    	case 3:
    		result = result * 0.5;
    		break;
    	default:
    		result = result * 1.0;
    		break;
    }
    
    return result;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only use this prayer on " +
           "yourself!\n");
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

    if (caster_is_maintaining_dynami_effects(caster)) 
    {
    	write("You cannot use this prayer while maintaining dynami.\n");
    	return 0;
    }  

    if (caster_is_maintaining_evimero_effects(caster)) 
    {
    	write("You cannot use this prayer while maintaining evimero.\n");
    	return 0;
    }      

    if (caster_is_maintaining_schirmo_effects(caster)) 
    {
    	write("You cannot use this prayer while maintaining schirmo.\n");
    	return 0;
    }      	 

    return 1;
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_THALAMOS)
    {
        return 0;
    }

    // Only master clerics and higher get this spell
    if (GUILD_MANAGER->query_is_child_cleric(player))
    {
        return 0;
    }
    
    // Only spirit clerics get this spell
    if (GUILD_MANAGER->query_primary_element(player) != "life")
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

    caster_message = "You close your eyes while mentally focusing on the " +
        "sacred Thalamos prayer, calling upon Psuchae to ward against the " +
        "Soulless.\n";
    watcher_message = QCTNAME(caster)+" closes "+caster->query_possessive()+ 
       " eyes and focuses inward in silent prayer.\n";
        
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
		    caster->catch_tell("\n\nYou have deliberately violated your "+
		        "Vow of Service. The Conduit between the Circle and the "+
		        "Five suffers from your lack of Faith.\n\n\n");
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

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already protected by the thalamos prayer!\n");
}

/*
 * Function:    query_stoneskin_ingredients
 * Description: This function defines what components are required for
 *              this stoneskin spell.
 */
public string *
query_stoneskin_ingredients(object caster)
{
    return ({ "_psuchae_component_" });
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
    return "psuchae component (drakeroot, alexandrite shard)";
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
