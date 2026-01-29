/*
 * Detect Resistances Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, January 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "detect_resistance";
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
 * Description: Config function for detect_resistance spells. Redefine this 
 *              in your own detect_resistance spells to override the defaults.
 */
public void
config_detect_resistance_spell()
{
    set_spell_name("antistasi");
    set_spell_desc("Detect resistances");

    set_spell_element(SS_ELEMENT_WATER, 30);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_2);

    // Needs to be particularly easy to cast to break through some resistances
    set_spell_task(TASK_SIMPLE);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_target(spell_target_one_present_living);

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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_ANTISTASI)
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
    
    // Only water clerics get this spell
    if (GUILD_MANAGER->query_primary_element(player) != "water")
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
    
    if (caster == target)
        caster_message = "You pray to Lord Diabrecho while gesturing towards "+ 
            "yourself.\n";
    else
        caster_message = "You pray to Lord Diabrecho while gesturing towards "+ 
            QTNAME(target) + ".\n";
            
    watcher_message = QCTNAME(caster) + " gestures mysteriously " + 
          "while concentrating.\n";
        
    caster->catch_msg(caster_message);
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
		    caster->catch_tell("\n\nYou have acted outside of your Vow of "+
		        "Service. This strains your connection with the Circle and "+
		        "the Conduit.\n\n\n");
    		break;
    	case 2:  // halved conduit gain, double conduit cost
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
		    caster->catch_tell("\n\nYou have deliberately violated your Vow "+
		        "of Service. The Conduit between the Circle and the Five "+
		        "suffers from your lack of Faith.\n\n\n");
    		break;
    	case 3:  // halved conduit gain, double conduit cost, halved CAID
    		GUILD_MANAGER->add_practice_level(caster, 5);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
		    GUILD_MANAGER->add_guild_conduit(5);
		    caster->catch_tell("\n\nYou have repeatedly violated your Vow "+
		        "of Service. With such malpractice, your prayers sound "+
		        "weak and hollow.\n\n\n");
    		break;
    	default:
    		GUILD_MANAGER->add_practice_level(caster, 10);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 10);
		    GUILD_MANAGER->add_guild_conduit(10);
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
hook_detect_resistance_cast(object caster)
{
}

/*
 * Function:    hook_detect_resistance_resisted
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_resistance_resisted(object caster, object target, int resistance)
{
    if (caster == target)
        caster->catch_msg("You resist your attempt to divine "
            + "any magical resistances.\n");
    else
        caster->catch_msg(QCTNAME(target) + " resists your attempt to divine "
            + "any magical resistances.\n");
}

string
reword_element(string element)
{
   string new_element;

   switch(element)
   {
     case "_magic_i_res_electricity":
      new_element = "electricity";
      break;
     case "_magic_i_res_poison":
      new_element = "poison";
      break;
     case "_magic_i_res_identify":
      new_element = "identification spells";
      break;
     case "_magic_i_res_life":
      new_element = "life magic";
      break;
     case "_magic_i_res_water":
      new_element = "water magic";
      break;
     case "_magic_i_res_air":
      new_element = "air magic";
      break;
     case "_magic_i_res_fire":
      new_element = "fire magic";
      break;
     case "_magic_i_res_death":
      new_element = "death magic";
      break;
     case "_magic_i_res_earth":
      new_element = "earth magic";
      break;
     case "_magic_i_res_magic":
      new_element = "magic in general";
      break;
     case "_magic_i_res_cold":
      new_element = "the cold";
      break;
     case "_magic_i_res_acid":
      new_element = "acid";
      break;
     case "_magic_i_res_life":
      new_element = "life magic";
      break;
     case "_magic_i_res_illusion":
      new_element = "illusion spells";
      break;
     default:
      new_element = "something you are unable to define";
    }

  return new_element;
}

 
/*
 * Function:    hook_detect_resistance_living_results
 * Description: Override this function to describe what a player should see
 *              when they are detecting magic on a living being.
 */
public void
hook_detect_resistance_success(object caster, object target, mapping resistances)
{
    int detect_resist = 0;

    if (caster == target)
        caster->catch_msg("You divine the following from yourself:\n");
    else
        caster->catch_msg("You divine the following from " +QTNAME(target)+
            ":\n");
        
    foreach (string element, int resistance : resistances)
    {
      string new_element = reword_element(element);

      switch(resistance)
      {
        case -200..-61:
         caster->catch_msg("You detect extreme vulnerability to " +
             new_element + ".\n");
         detect_resist = 1;
         break;
        case -60..-41:
         caster->catch_msg("You detect high vulnerability to " +
             new_element + ".\n");
         detect_resist = 1;
         break;
        case -40..-31:
         caster->catch_msg("You detect considerable vulnerability to " +
             new_element + ".\n");
         detect_resist = 1;
         break;
        case -30..-11:
         caster->catch_msg("You detect some vulnerability to " +
             new_element + ".\n");
         detect_resist = 1;
         break;
        case -10..-1:
         caster->catch_msg("You detect minor vulnerability to " +
             new_element + ".\n");
         detect_resist = 1;
         break;
        case 0:
         break;
        case 1..10:
         caster->catch_msg("You detect minor resistance to " +
             new_element + ".\n");
         detect_resist = 1;
         break;
        case 11..30:
         caster->catch_msg("You detect some resistance to " +
             new_element+ ".\n");
         detect_resist = 1;
         break;
        case 31..40:
         caster->catch_msg("You detect considerable resistance to " +
             new_element+ ".\n");
         detect_resist = 1;
         break;
        case 41..60:
         caster->catch_msg("You detect high resistance to " +
             new_element+ ".\n");
         detect_resist = 1;
         break;
        case 61..80:
         caster->catch_msg("You detect extreme resistance to " +
             new_element+ ".\n");
         detect_resist = 1;
         break;
        default:
         caster->catch_msg("You detect almost invulnerability to " +
             new_element+ ".\n");
         detect_resist = 1;
      }
    }

    if(!detect_resist)
        if (caster == target)
            caster->catch_msg("You appear to have no magical resistances.\n");
        else
            caster->catch_msg(QCTNAME(target)+ " appears to have no magical "+
                "resistances.\n");
}

/*
 * Function:    query_detect_resistance_ingredients
 * Description: This function defines what components are required for 
 *              this detect_resistance spell.
 */
public string *
query_detect_resistance_ingredients(object caster)
{

    return ({ "_antistasi_component_" });
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
    return "antistasi component (skull, sapphire shard)";
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
