/*
 * Resistance Spell for the Elemental Clerics of Calia
 *
 * Created by Jaacar, January 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/resistance";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// Prototypes
public object * spell_target_unteristi(object actor, string str);
public int      query_spell_resistance_amount = 15;

/*
 * Function:    is_cleric_child_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_cleric_child_spell()
{
    return 1;
}

/*
 * Function:    config_resistance_spell
 * Description: Config function for resistance spells. Redefine this in your
 *              own resistance spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_resistance_spell()
{
    set_spell_name("unteristi");
    set_spell_desc("Enshroud with elemental resistance");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_element(SS_ELEMENT_LIFE, 20); // see query_spell_element_skill
    set_spell_form(SS_FORM_ABJURATION, 20);    
    
    set_spell_target(spell_target_unteristi);
    
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

    string primary_element = GUILD_MANAGER->query_primary_element(player);
    int element_skill = SS_ELEMENT_FIRE + random(5); // randomize by default
    switch (primary_element)
    {
    case "fire":
        element_skill = SS_ELEMENT_FIRE;
        query_spell_resistance_amount = 15;
        set_spell_object(ELEMENTALIST_SPELL_OBJS + "unteristi_obj");
        break;
    
    case "earth":
        element_skill = SS_ELEMENT_EARTH;
        query_spell_resistance_amount = 15;
        set_spell_object(ELEMENTALIST_SPELL_OBJS + "unteristi_obj");
        break;
    
    case "water":
        element_skill = SS_ELEMENT_WATER;
        query_spell_resistance_amount = 15;
        set_spell_object(ELEMENTALIST_SPELL_OBJS + "unteristi_obj");
        break;
    
    case "air":
        element_skill = SS_ELEMENT_AIR;
        query_spell_resistance_amount = 15;
        set_spell_object(ELEMENTALIST_SPELL_OBJS + "unteristi_obj");
        break;
        
    case "life":
        element_skill = SS_ELEMENT_LIFE;
        query_spell_resistance_amount = 15;
        set_spell_object(ELEMENTALIST_SPELL_OBJS + "unteristi_obj");
        break;
    }
    
    add_resistance(MAGIC_I_RES_FIRE,  query_spell_resistance_amount);
	add_resistance(MAGIC_I_RES_WATER, query_spell_resistance_amount);
	add_resistance(MAGIC_I_RES_AIR,   query_spell_resistance_amount);
	add_resistance(MAGIC_I_RES_EARTH, query_spell_resistance_amount);
	add_resistance(MAGIC_I_RES_DEATH, query_spell_resistance_amount);
	add_resistance(MAGIC_I_RES_LIFE,  query_spell_resistance_amount);    
    return element_skill;
}

public object *
spell_target_unteristi(object caster, string str)
{
    return spell_target_caster(caster, str);
}

/*
 * Function:    query_resistance_ingredients
 * Description: This function defines what components are required for
 *              this resistance spell.
 */
public string *
query_resistance_ingredients(object caster)
{
    return ({  });
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_UNTERISTI)
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
        caster_message = "You hold out your palms and lift up a prayer "
            + "to all the Elementals.\n";
        watcher_message = QCTNAME(caster) + " holds out "
            + caster->query_possessive() + " palms and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You clasp your hands and fervently pray to all "
            + "the elementals to grant you the protective gifts of "
            + query_spell_name() + ".\n";
        watcher_message = QCTNAME(caster) + " clasps " + 
        	caster->query_possessive()
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
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have acted outside of your "+
		    	"Vow of Service. "+
		        "This strains your connection with the Circle and "+
		        "the Conduit.\n\n\n");
    		break;
    	case 2:  // halved conduit gain, double conduit cost
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have deliberately violated your "+
		    	"Vow of Service. "+
		        "The Conduit between the Circle and the Five suffers from "+
		        "your lack of Faith.\n\n\n");
    		break;
    	case 3:  // halved conduit gain, double conduit cost, halved CAID
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have repeatedly violated your "+
		    	"Vow of Service. "+
		        "With such malpractice, your prayers sound weak and "+
		        "hollow.\n\n\n");
    		break;
    	default:
    		GUILD_MANAGER->add_practice_level(caster, 2);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
		    GUILD_MANAGER->add_guild_conduit(2);
    		break;
    }   
}

/*
 * Function:    resolve_resistance_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_resistance_spell(object caster, mixed * targets, 
	int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already invoked the gift of " + query_spell_name() + "!\n");
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already 
 *              existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{	
    write("You renew the effects of the gift of " + query_spell_name() + 
        " on yourself!\n");
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
 * Function:    hook_describe_cast_resistance
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_resistance(object caster, object * targets)
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
