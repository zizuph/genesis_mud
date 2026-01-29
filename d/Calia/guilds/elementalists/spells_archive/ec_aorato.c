/*
 * Invisibility Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, January 2017
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/invisibility";
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
 * Function:    config_invisibility_spell
 * Description: Config function for invisibility spells. Redefine this in your
 *              own spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_invisibility_spell()
{
    set_spell_name("aorato");
    set_spell_desc("Invisibility");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_offensive(0);
    set_spell_peaceful(1);
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_ABJURATION, 40);
    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");   

    // Can only cast invisibility on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_shadow_filename(ELEMENTALIST_SPELL_OBJS + "invisibility_sh");
}

/*
 * Function:    query_invisibility_ingredients
 * Description: This function defines what components are required for
 *              this evade spell.
 */
public string *
query_invisitibility_ingredients(object caster)
{
    return ({ "_aorato_component_" });
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_AORATO)
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

        caster_message = "You draw upon the powers of the shadows.\n";
        watcher_message = QCTNAME(caster) + " concentrates intensely.\n";
        
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


/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg("You are already invisible in the shadow realms!\n");
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
    return "aorato component (eye, alexandrite shard)";
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
