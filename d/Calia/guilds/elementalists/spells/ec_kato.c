/*
 * Lower Resistance Spell for the Elemental Clerics of Calia
 *
 * Created by Jaacar, February 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "propchange_base";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// The reduced CAID is the caid left in schirmo, unteresti,dynami and evimero
// if the boosted aspida is active. Elefrinisi can't be cast if aspida boosted.

#define REDUCED_CAID      (REDUCED_BASE_AID * 4.0)
#define MAX_CAID          (BASE_KATO_AID + ELEFRINISI_AID + \
 SCHIRMO_AID + UNTERISTI_AID + DYNAMI_AID + EVIMERO_AID - REDUCED_CAID)

#define DEBUG(x)  find_player("arman")->catch_msg("[ec_kato] " + x + "\n")


// Prototypes
public object * spell_target_kato(object actor, string str);

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
 * Function:    config_propchange_spell
 * Description: Config function for propchange spells. Redefine this in your
 *              own propchange spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_propchange_spell()
{
    set_spell_name("kato");
    set_spell_desc("Lower elemental resistance");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_4);
    set_spell_combat_aid(MAX_CAID);

    set_spell_offensive(1);

    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_ABJURATION, 40);

    set_shadow_filename(ELEMENTALIST_SPELL_OBJS + "kato_sh");    
    
    set_spell_target(spell_target_kato);
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    // This modifier to caid only works for altering dynamic mana
    // cost. Any changes to the formula would need to be reflected
    // in the shadow object as well (at least until the base spell
    // gets fixed to better take into account caid).

    float result;

    // modify base caid by active maintained spells.
    float total_combat_aid = MAX_CAID;
    float available_combat_aid = BASE_KATO_AID;

    if (!caster_is_maintaining_elefrinisi_effects(TP)) 
    {
        // DEBUG("Elefrinisi aid added to kato.\n");
        available_combat_aid += ELEFRINISI_AID;
    }

    if (!caster_is_maintaining_unteristi_effects(TP)) 
    {
        // DEBUG("unteristi aid added to kato.\n");
        available_combat_aid += UNTERISTI_AID;

        // Unteristi et al have a minimum value
        // which needs to be taken into account if
        // activated after this spell is cast.
        available_combat_aid -= REDUCED_BASE_AID;
    }

    if (!caster_is_maintaining_dynami_effects(TP) &&
        !caster_is_maintaining_thalamos_effects(TP)) 
    {
        // DEBUG("dynami aid added to kato.\n");
        available_combat_aid += DYNAMI_AID;
        available_combat_aid -= REDUCED_BASE_AID;
    }

    if (!caster_is_maintaining_evimero_effects(TP) &&
        !caster_is_maintaining_thalamos_effects(TP)) 
    {
        // DEBUG("evimero aid added to kato.\n");
        available_combat_aid += EVIMERO_AID;
        available_combat_aid -= REDUCED_BASE_AID;
    }

    if (!caster_is_maintaining_schirmo_effects(TP) &&
        !caster_is_maintaining_thalamos_effects(TP)) 
    {
        // DEBUG("schirmo aid added to kato.\n");
        available_combat_aid += SCHIRMO_AID;
        available_combat_aid -= REDUCED_BASE_AID;
    }

    // DEBUG("kato available_combat_aid: " +ftoi(available_combat_aid));
    // DEBUG("kato max potential combat aid: " +ftoi(total_combat_aid));

    result = (available_combat_aid / total_combat_aid) * 100.0;
    
    // Has guru quest been completed? If so, set at 60, otherwise 40
    if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    {
    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
    		result = result * 0.5;

        return result;
    }

    if (TP->query_prop(CONDUIT_PENALTY) == 3)
        result = result * 0.34;
    else
    	result = result * 0.67;

    return result;
}

public object *
spell_target_kato(object caster, string str)
{
	string element_string, target_string;
	
	parse_command((strlen(str) ? str : ""), environment(caster),
	    "[on] %w", target_string);
	caster->add_prop("_kato_prop","magic");  // general
    
    if (!target_string)
    {
    	caster->catch_tell("Who do you want to decrease resistance on?\n");
        return 0;
    }
    
    return spell_target_one_present_living(caster, target_string);
}

/*
 * Function:    query_propchange_ingredients
 * Description: This function defines what components are required for
 *              this propchange spell.
 */
public string *
query_propchange_ingredients(object caster)
{
    return ({ "_spirit_component_" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    /*
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    */
    
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
    
    if (caster->query_prop("_live_i_cast_kato"))
    {
        write("You are already maintaining the gift of Kato. You will "+
            "have to dispel that first before you can use it again.\n");
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_KATO)
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
    switch (random(2))
    {
    case 0:
        caster_message = "You hold out your palms and pray "
            + "to Psuchae to grant you the gift of kato.\n";
        watcher_message = QCTNAME(caster) + " holds out "
            + caster->query_possessive() + " palms and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You clasp your hands and fervently pray to "
            + "Psuchae to grant you the gift of "
            + query_spell_name() + ".\n";
        watcher_message = QCTNAME(caster) + " clasps " 
            + caster->query_possessive()
            + " hands together and concentrates.\n";
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
 * Function:    resolve_propchange_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_propchange_spell(object caster, mixed * targets, int * resist,
                           int result, mapping spell_input)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    /*
    if (caster == target)
    	write("You have already invoked the gift of " + query_spell_name() +
    	    " on yourself!\n");
    else
    	write("You have already invoked the gift of " + query_spell_name() +
    	    " on " + target->query_the_name(caster) + "!\n");
    	    */
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
 * Function:    hook_describe_cast_propchange
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_propchange(object caster, object * targets)
{
    // We don't display anything here. All messages are in the spell
    // object
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
    return "spirit component (drakeroot, onyx shard)";
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
