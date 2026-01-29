/*
 * Identify Magic Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, January 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <files.h>
#include <flags.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "identify";

/*
 * Function:    config_identify_spell
 * Description: Config function for identify spells. Redefine this in your
 *              own identify spells to override the defaults.
 */

public void
config_identify_spell()
{
    set_spell_name("magikos");
    set_spell_desc("Divine the magical properties of an item");

    set_spell_element(SS_ELEMENT_LIFE, 30);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_2);

}

/*
 * Function:    resolve_identify_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_identify_spell(object caster, mixed * targets, int * resist, int result)
{
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_MAGIKOS)
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

    caster->catch_tell("You mentally concentrate on " + 
        FO_COMPOSITE_ALL_DEAD(({ targets[0] }), caster) + " while praying "+
        "to " +
        "Psuchae for guidance.\n");
    object * who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,
        all_inventory(environment(caster)) - ({ caster })));

    who->catch_msg(QCTNAME(caster) + " appears to concentrate " + 
        "on something and mumbles something under "+caster->query_possessive()+ 
        " breath.\n");
        
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
		    	"Service. "+
		        "This strains your connection with the Circle and the "+
		        "Conduit.\n\n\n");
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
		    caster->catch_tell("\n\nYou have repeatedly violated your Vow "+
		    	"of Service. "+
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
 * Function:    hook_identify_sucess
 * Description: Mask this function to change the description of when
 *              the object is successfully identified.
 */
public void
hook_identify_success(object caster, object target, string id_message, int result)
{
    if (!objectp(caster) || !objectp(target))
    {
        return;
    }
    caster->catch_tell(id_message);

}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    object mandala = present("_elemental_guild_mandala", caster);
    if (!mandala)
    {
        write("You cannot use this prayer without your sacred mandala!\n");
        return 0;
    }

    object target = targets[0];

    if (IS_LIVING_OBJECT(target))
    {
        caster->catch_tell("You can only use this prayer on items, not " +
           "living creatures.\n");
        return 0;
    }
  
    return 1;
}

/*
 * Function:    query_identify_ingredients
 * Description: This function defines what components are required for
 *              this identify spell.
 */
public string *
query_identify_ingredients(object caster)
{
    return ({  });
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
