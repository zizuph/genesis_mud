/*
 * Shadow Wall Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, February 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include <composite.h>
#include <time.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "light";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

public string direction = "";
public int wall_time;


/*
 * Function name:   disable_pvp_abilities
 * Description:     Created to enable the override of pvp abilities.
 * Arguments:       (object) actor
 * Returns:         (status) 1 - Abilities disabled
 *                           0 - Abilities enabled
 */
public nomask status
disable_pvp_abilities(object actor)
{
    return PVP_ABILITY_DISABLED;
} /* disable_pvp_abilities */


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
 * Use this to determine the direction
 */
 
public object *
spell_target_direction(object caster, string str)
{
    string who, dir;
    object* targets;
    object* existing_walls;

    int i;

    if (!strlen(str))
    {
        caster->catch_tell("You must specify a direction to summon the "+
        	"shadow wall.\n");
        return ({});
    }

    if (!(IN_ARRAY(str, environment(caster)->query_exit_cmds())))
    {
        caster->catch_tell("That is not a valid exit for the prayer!\n");
        return ({});
    }

    existing_walls = filter(all_inventory(environment(caster)), 
    	&->id("_EC_shadow_wall"));

    for(int i = 0; i < sizeof(existing_walls); i++)
    {
      if(existing_walls[i]->query_blocked_exit() == str)
      {
            caster->catch_tell("There is already a shadow wall blocking "+
            	"that path!\n");
            return ({ });
      }
    }

    direction = str;

    return (({caster}));
}

/*
 * Function:    config_light_spell
 * Description: Config function for light spells. Redefine this in your
 *              own light spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_light_spell()
{
    set_spell_name("tihosskias");
    set_spell_desc("Shadow wall");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_can_be_renewed(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_task(TASK_HARD);    
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
    
    set_spell_target(spell_target_direction);

    set_spell_ingredients(query_light_ingredients);
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "tihosskias_obj");
    
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_TIHOSSKIAS)
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

/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" resisted your prayer.\n");

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
    
    int cooldown = caster->query_prop(LIVE_I_TIHOSSKIAS_CAST);
    if (cooldown) 
    {
    	if (cooldown > time())
    	{
	    	caster->catch_msg("You are not yet ready to use the gift of "+
	    	    "Tihosskias again for another " + (cooldown - time()) + 
	    	    " seconds.\n");
	    	return 0;
	    }
    }

    if (present("_cast_shadow_wall_object_", caster))
    {
        caster->catch_msg("You have already blocked an exit using "+
            "tihosskias. You must dispel the one you have if you wish "+
            "to have another.\n");
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

    caster_message = "You close your eyes and concentrate on "+
        "the powers granted to you by Psuchae.\n";
    watcher_message = QCTNAME(caster)+" closes "+caster->query_possessive()+ 
       " eyes.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    setuid();
    seteuid(getuid());
    int conduit_penalty = caster->query_prop(CONDUIT_PENALTY);
    caster->add_prop("_shadow_wall_cast",direction);
    
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

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already blocked an exit using "+
        "tihosskias. You must dispel the one you have if you wish "+
        "to have another.\n");
}

/*
 * Function:    hook_no_light_message
 * Description: When it is not possible to light, for whatever reason,
 *              this message is given.
 * Arguments:   caster - person casting the spell
 *              target - the person being lighted
 */
public void
hook_no_light_message(object caster, object target)
{
    caster->catch_tell("Your cannot seem to locate your target.\n");    
}

/*
 * Function:    query_light_ingredients
 * Description: This function defines what components are required for
 *              this light spell.
 */
public string *
query_light_ingredients(object caster)
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
