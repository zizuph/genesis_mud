/*
 * Elemental Summoning Spell for the Elementalists of Calia
 * 
 * This is the summoning spell that allows an Elementalist of Calia to summon
 * one of the four elementals (one from each Prime Elemental). It is based
 * on the Genesis Magic System's generic summon spell.
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

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "summon";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// Defines
#define CHOMA_ELEMENT          "_choma_element"

// Prototypes
public object * spell_target_caster_choma(object caster, string str);

/*
 * Function:    config_summon_spell
 * Description: Config function for summon spells. Redefine this in your
 *              own summon spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_summon_spell()
{
    setuid();
    seteuid(getuid());
    set_spell_name("choma");
    set_spell_desc("Summon elemental");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_ROUTINE);
    set_spell_target(spell_target_caster_choma);
    set_spell_ingredients(query_summon_ingredients);

    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_CONJURATION, 15);
    
    set_summon_file(ELEMENTALIST_SPELL_OBJS + "choma_obj");

    set_summon_into_inventory(0);
    
    // Set the effect object filename
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "choma_spell_obj");
}

/*
 * Function:    query_spell_element_skill
 * Description: Returns the actual element skill number that is required
 *              for the spell.
 */
public int
query_spell_element_skill()
{
    // This should end up returning whatever specialization the player
    // has for the skill.
    object player = this_player();

    // Spell's element is determined during concentrate_msg and stored.
    int element_skill = player->query_prop(CHOMA_ELEMENT);
        
    return element_skill;
}

/*
 * Function:    spell_target_caster_choma
 * Description: A targeting function specific for choma. It needs to
 *              parse out the string and set the correct element for
 *              the summoning
 */
public object *
spell_target_caster_choma(object caster, string str)
{
    string element_string, target_string;
    int element_skill = 0;   
    parse_command((strlen(str) ? str : ""), environment(caster),
        "[to] %w [on] %w", element_string, target_string);
    if (strlen(element_string))
    {
        switch (lower_case(element_string))
        {
        case "pyros":
            element_skill = SS_ELEMENT_FIRE;
            break;
        case "aeria":
            element_skill = SS_ELEMENT_AIR;
            break;
        case "gu":
            element_skill = SS_ELEMENT_EARTH;
            break;
        case "diabrecho":
            element_skill = SS_ELEMENT_WATER;
            break;
        case "psuchae":
        	element_skill = SS_ELEMENT_LIFE;
        	break;
        }
    }
    if (!element_skill)
    {
        caster->catch_tell("To which Elemental do you wish to request a "+
            "summoning? Pyros, Aeria, Gu, Diabrecho or Psuchae?\n");
        return 0;
    }
            
    caster->add_prop(CHOMA_ELEMENT, element_skill);
    
    if (caster->is_elemental_racial_cleric())
    {
        set_summon_file(ELEMENTALIST_SPELL_OBJS + "choma_steed_obj");
    }
    else
    {
    	set_summon_file(ELEMENTALIST_SPELL_OBJS + "choma_obj");
    }   
    
    return spell_target_caster(caster, target_string);
}

/*
 * Function name: has_choma_object
 * Description:   Checks to see if the target already has one of the choma
 *                shields.
 */
public int 
has_choma_object(object target)
{
    object * effects = GUILD_MANAGER->get_existing_choma_objects(target);
    if (sizeof(effects))    
    {   
        return 1;
    }
    
    return 0;
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

    if (has_choma_object(caster))
    {
        caster->catch_tell("You already have summoned an elemental!\n");
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_CHOMA)
    {
        return 0;
    }
    return 1;
}

public string
query_spell_patron()
{
    switch (query_spell_element_skill())
    {
    case SS_ELEMENT_FIRE:
        return "Lord Pyros";
    
    case SS_ELEMENT_EARTH:
        return "Lady Gu";
    
    case SS_ELEMENT_WATER:
        return "Lord Diabrecho";
    
    case SS_ELEMENT_AIR:
        return "Lady Aeria";
        
    case SS_ELEMENT_LIFE:
    	return "Psuchae";
    	
    }
    
    return "the Elementals";
}

public string
query_spell_patron_pronoun()
{
    switch (query_spell_element_skill())
    {
    case SS_ELEMENT_FIRE:
    case SS_ELEMENT_WATER:
        return "he";

    case SS_ELEMENT_EARTH:
    case SS_ELEMENT_AIR:
        return "she";
    }
    
    return "they";
}

public string
query_spell_patron_objective()
{
    switch (query_spell_element_skill())
    {
    case SS_ELEMENT_FIRE:
    case SS_ELEMENT_WATER:
        return "him";

    case SS_ELEMENT_EARTH:
    case SS_ELEMENT_AIR:
        return "her";
    }
    
    return "them";
}

public string
query_spell_patron_possessive()
{
    switch (query_spell_element_skill())
    {
    case SS_ELEMENT_FIRE:
    case SS_ELEMENT_WATER:
        return "his";

    case SS_ELEMENT_EARTH:
    case SS_ELEMENT_AIR:
        return "her";
    }
    
    return "their";
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
    switch (random(3))
    {
    case 0:
        caster_message = "You begin to murmur the choma incantation, calling "
            + "out to " + query_spell_patron() + " to send you a servant of "
            + "the Elementals.\n";
        watcher_message = QCTNAME(caster) + " begins to murmur a strange "
            + "incantation.\n";
        break;
    
    default:
    case 1:
        caster_message = "You begin a prayer to " + query_spell_patron()
            + " asking that " + query_spell_patron_pronoun() + " might "
            + "grant you the use of one of " + query_spell_patron_possessive()
            + " servants.\n";
        watcher_message = QCTNAME(caster) + " begins to murmur a strange "
            + "incantation.\n";
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
		        "Service. This strains your connection with the Circle and "+
		        "the Conduit.\n\n\n");
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
		    caster->catch_tell("\n\nYou have repeatedly violated your Vow "+
		        "of Service. With such malpractice, your prayers sound "+
		        "weak and hollow.\n\n\n");
    		break;
    	default:
    		GUILD_MANAGER->add_practice_level(caster, 2);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
		    GUILD_MANAGER->add_guild_conduit(2);
    		break;
    }
}

/*
 * Function:    resolve_summon_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_summon_spell(object caster, mixed * targets, int * resist, int result, mapping input)
{
    switch (query_spell_element_skill())
    {
    case SS_ELEMENT_FIRE:
        input["element"] = "fire";
        break;
    
    case SS_ELEMENT_WATER:
        input["element"] = "water";
        break;
    
    case SS_ELEMENT_EARTH:
        input["element"] = "earth";
        break;
    
    case SS_ELEMENT_AIR:
        input["element"] = "air";
        break;
        
    case SS_ELEMENT_LIFE:
        input["element"] = "life";
        break;
    }
}

/*
 * Function:    query_summon_ingredients
 * Description: This function defines what components are required for
 *              this summon spell.
 */
public string *
query_summon_ingredients(object caster)
{
    return ({  });
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already summoned an elemental using the " 
        + query_spell_name() + " gift!\n");
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
        + "the power of choma.\n");
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
