/*
 * Teleport Spell for the Elemental Clerics of Calia
 *
 * Created by Petros, August 2011
 * Moved location to Greathall from library - Jaacar, June 2016
 * Modified for Clerics - Jaacar, January 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "teleport";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// Prototypes
public object * spell_target_teleport(object actor, string str);

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
 * Function:    config_teleport_spell
 * Description: Config function for teleport spells. Redefine this in your
 *              own teleport spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_teleport_spell()
{
    set_spell_name("apodosi");
    set_spell_desc("Teleport self");

    set_spell_target(spell_target_teleport);

    ::config_teleport_spell();
    
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_4);
    set_spell_element(SS_ELEMENT_WATER, 10);
    set_spell_form(SS_FORM_CONJURATION, 15);
}

public object *
spell_target_teleport(object caster, string str)
{
    string arg;
    object env = environment(caster);
    string  target_room_file;
    
    mapping locations = GUILD_MANAGER->query_teleport_locations(caster);
    
    if (GUILD_MANAGER->query_is_child_cleric(caster))
    {
        // Safely load the default start location. 
        // See /d/Sparkle/area/city/lib/utility_functions for implementation.
        string target_room_file = ELEMENTALIST_TEMPLE + "greathall";
        setuid();
        seteuid(getuid());
        object target_room = safely_load_master_file(target_room_file);
        return ({ target_room, caster });
    }  
    
    if (!stringp(str))
    {
        // Safely load the default start location. 
        // See /d/Sparkle/area/city/lib/utility_functions for implementation.
        string target_room_file = ELEMENTALIST_TEMPLE + "greathall";
        setuid();
        seteuid(getuid());
        object target_room = safely_load_master_file(target_room_file);
        return ({ target_room, caster });
    }        
        
    if(parse_command(str, env, "[to] %s", arg))
    {
        if (member_array(lower_case(arg), m_indexes(locations)) < 0)
        {
            write("You haven't set a location to teleport to by that name.\n");
            return ({ });
        }
    }
    
    setuid();
    seteuid(getuid());

    target_room_file = locations[lower_case(arg)];
    object target_room = safely_load_master_file(target_room_file);

    return ({ target_room, caster }); 
}

// If teleporting home, avoid the targeted location penalty.
int get_next_teleport_delay(object caster, object destination)
{
    if (destination 
      && MASTER_OB(destination) == ELEMENTALIST_TEMPLE + "greathall")
    {
        return DEFAULT_TELEPORT_TO_HOME_DELAY;
    }
    return ::get_next_teleport_delay(caster, destination);
}


/*
 * Function:    query_teleport_ingredients
 * Description: This function defines what components are required for
 *              this haste spell.
 */
public string *
query_teleport_ingredients(object caster)
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_APODOSI)
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
    
    if (GUILD_MANAGER->query_is_child_cleric(caster))
    {        
        switch (random(2))
        {
        case 0:
            caster_message = "You bow your head in prayer to Lord Diabrecho "
                + "to carry you to your destination.\n";
            watcher_message = QCTNAME(caster) + " bows " +
                caster->query_possessive()
                + " head in prayer.\n";
            break;
        
        case 1:
        default:
            caster_message = "You stomp your feet and loudly chant the ancient "
                + "prayer of apodosi to Lord Diabrecho, requesting passage by "
                + "water.\n";
            watcher_message = QCTNAME(caster) + " stomps " +
                caster->query_possessive()
                + " feet and loudly chants an ancient prayer.\n";
            break;
        }
    }
    
    else 
    {
    	if (GUILD_MANAGER->query_primary_element(caster) != "air")
	    {        
	        switch (random(2))
	        {
	        case 0:
	            caster_message = "You bow your head in prayer to Lord "
	                + "Diabrecho to carry you to your destination.\n";
	            watcher_message = QCTNAME(caster) + " bows " +
	                caster->query_possessive()
	                + " head in prayer.\n";
	            break;
	        
	        case 1:
	        default:
	            caster_message = "You stomp your feet and loudly chant the "+
	                "ancient prayer of apodosi to Lord Diabrecho, requesting "+
	                "passage by water.\n";
	            watcher_message = QCTNAME(caster) + " stomps " +
	                caster->query_possessive()
	                + " feet and loudly chants an ancient prayer.\n";
	            break;
	        }
	    }
    
	    if (GUILD_MANAGER->query_primary_element(caster) == "air")
	    {        
	        switch (random(2))
	        {
	        case 0:
	            caster_message = "You bow your head in prayer to Lady Aeria "
	                + "to carry you to your memorized location.\n";
	            watcher_message = QCTNAME(caster) + " bows " +
	                caster->query_possessive()
	                + " head in prayer.\n";
	            break;
	        
	        case 1:
	        default:
	            caster_message = "You stomp your feet and loudly chant the "+
	                "ancient prayer of apodosi to Lady Aeria, requesting "+
	                "passage by air.\n";
	            watcher_message = QCTNAME(caster) + " stomps " +
	                caster->query_possessive()
	                + " feet and loudly chants an ancient prayer.\n";
	            break;
	        }
	    }
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
		    caster->catch_tell("\n\nYou have deliberately violated your Vow "+
		        "of Service. The Conduit between the Circle and the Five "+
		        "suffers from your lack of Faith.\n\n\n");
    		break;
    	case 3:  // halved conduit gain, double conduit cost, halved CAID
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have repeatedly violated your Vow "+
		        "of Service. With such malpractice, your prayers sound weak "+
		        "and hollow.\n\n\n");
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
resolve_teleport_spell(object caster, mixed * targets, int * resist, int result)
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
    write("You need a proper ritual component as part of "
        + "the gift of " + query_spell_name() + ".\n");
}

/*
 * Function:    hook_cannot_teleport_caster_in_combat
 * Description: Hook that gets called when trying to teleport while in combat.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_caster_in_combat(object caster, mixed * targets, string arg, int execute)
{
    if (!execute)
    {
        caster->catch_tell("You cannot travel via apodosi while you are "+
            "in combat.\n");
    }
    else
    {
        caster->catch_tell("You lose your concentration of your apodosi "+
            "prayer as you are distracted by combat.\n");
    }
}

/*
 * Function:    hook_cannot_teleport_target_not_relaxed
 * Description: Hook that gets called when trying to teleport while having
 *              recently been in combat.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_target_not_relaxed(object caster, object target, string arg, int execute)
{
    caster->catch_tell("You have too recently been in combat. You have to "
        + "relax first before you can invoke the gift of apodosi.\n");
}

/*
 * Function:    hook_cannot_teleport_target_too_soon
 * Description: Hook that gets called when trying to teleport while having
 *              recently having teleported
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_target_too_soon(object caster, object target, string arg, int execute)
{
    caster->catch_tell("You have too recently teleported. You have to "
        + "wait before you can invoke the gift of apodosi.\n");
}

/*
 * Function:    hook_cannot_teleport_caster_room_not_valid
 * Description: Hook that gets called when the caster's current room is not 
 *              valid. It can be valid for a number of reasons. 
 *              See check_valid_action for the conditions checked.
 */
public void
hook_cannot_teleport_caster_room_not_valid(object caster, mixed * targets, string arg, int execute, object caster_room)
{
    caster->catch_tell("The room you are in prevents you from magically "+
        "departing.\n");
}

/*
 * Function:    hook_cannot_teleport_target_room_not_valid
 * Description: Hook that gets called when the spell's target room is not valid. It
 *              can be valid for a number of reasons. See check_valid_action 
 *              for the conditions checked.
 */
public void
hook_cannot_teleport_target_room_not_valid(object caster, mixed * targets, string arg, int execute, object target_room)
{
    caster->catch_tell("The room you want to reach prevents you from "+
        "magically transporting there.\n");
}

/*
 * Function:    hook_cannot_teleport_same_room
 * Description: Hook that gets called when the user is trying to teleport 
 *              to the same room that they are already in.
 */
public void             
hook_cannot_teleport_same_room(object caster, mixed * targets, string arg, int execute)
{
    caster->catch_tell("There's no need to call upon apodosi. You're "+
        "already there!\n");
}


/*
 * Function:    hook_describe_teleport_origin_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting out of the origin room.
 */
public void
hook_describe_teleport_origin_room(object caster, mixed* targets, object origin_room)
{
    //The targets for this spell should only contain the caster.
    
    if (GUILD_MANAGER->query_primary_element(caster) != "air")
    {
        caster->catch_tell("Tendrils of water suddenly appear from the ground "
            + "and slide up your body until they engulf you completely. As you "
            + "close your eyes, you feel yourself dissipating into the "
            + "water.\n");
        tell_room(origin_room, "Tendrils of water suddenly appear from the "
            + "ground and engulf " + QTNAME(caster) + " completely. As "
            + "the water recedes to the ground, " + caster->query_pronoun()
            + " is gone.\n", ({ caster }) );
    }
    
    if (GUILD_MANAGER->query_primary_element(caster) == "air")
    {
        caster->catch_tell("A whirlwind of air suddenly appears from above "
            + "and slides down your body until it engulfs you completely. As "
            + "you close your eyes, you feel yourself swirling around inside "
            + "the whirlwind.\n");
        tell_room(origin_room, "A whirlwind of air suddenly appears from "
            + "above and engulfs " + QTNAME(caster) + " completely. As "
            + "the whirlwind disappears above you, " + caster->query_pronoun()
            + " is gone.\n", ({ caster }) );
    }
    
}

/*
 * Function:    hook_describe_teleport_target_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting into the target room.
 */
public void
hook_describe_teleport_target_room(object caster, mixed* targets, object target_room)
{
    //The targets for this spell should only contain the caster.
    
    if (GUILD_MANAGER->query_is_child_cleric(caster))
    {
        caster->catch_tell("Opening your eyes again, you find yourself "
            + "back at the Elemental Temple.\n");
        tell_room(target_room, QCTNAME(caster) + " materializes from the "
        + "suddenly appearing pool of water on the ground with "
        + caster->query_possessive() + " eyes closed. "
        + capitalize(caster->query_pronoun()) + " opens them again, "
        + "glancing around.\n",  ({ caster }) );
    }
    
    else if (GUILD_MANAGER->query_primary_element(caster) != "air")
    {
        caster->catch_tell("Opening your eyes again, you find yourself "
            + "elsewhere.\n");
        tell_room(target_room, QCTNAME(caster) + " materializes from the "
        + "suddenly appearing pool of water on the ground with "
        + caster->query_possessive() + " eyes closed. "
        + capitalize(caster->query_pronoun()) + " opens them again, "
        + "glancing around.\n",  ({ caster }) );
    }
    
    else if (GUILD_MANAGER->query_primary_element(caster) == "air")
    {
        caster->catch_tell("Opening your eyes again, you find yourself "
            + "elsewhere.\n");
    tell_room(target_room, QCTNAME(caster) + " materializes from the "
        + "suddenly appearing whirlwind of air with "
        + caster->query_possessive() + " eyes closed. "
        + capitalize(caster->query_pronoun()) + " opens them again, "
        + "glancing around.\n",  ({ caster }) );
    }
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
