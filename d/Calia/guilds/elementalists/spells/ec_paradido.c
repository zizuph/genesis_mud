/*
 * Teleport to Known Player Spell for the Elemental Clerics of Calia
 *
 * Created by Jaacar, February 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "teleport";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

public object t_target;

// Prototypes
public object * spell_target_teleport(object actor, string str);

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
 * Function:    config_teleport_spell
 * Description: Config function for teleport spells. Redefine this in your
 *              own teleport spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_teleport_spell()
{
    set_spell_name("paradido");
    set_spell_desc("Teleport self to known player");

    set_spell_target(spell_target_teleport);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_4);

    set_spell_task(TASK_DIFFICULT);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_CONJURATION, 30);
}

public object *
spell_target_teleport(object caster, string str)
{
    string arg;
    object env = environment(caster);
    object  target_room_file;
        
    if (!stringp(str))
    {
        write("You have to specify who you want to teleport to.\n");
        return ({  });
    } 
        
    if(parse_command(str, env, "[to] %s", arg))
    {
        if (!caster->query_remembered(lower_case(arg)))
        {
            write("You don't have anyone by that name memorized.\n");
            return ({ });
        }
    }
    
    setuid();
    seteuid(getuid());
    
    if (!find_living(lower_case(arg)))
    {
    	write("You can't seem to find "+capitalize(arg)+" in the realms.\n");
    	return ({ });
    }
    
    if (find_player(lower_case(arg))->query_linkdead())
    {
    	write("You can't go to "+capitalize(arg)+" as they are linkdead.\n");
    	return ({ });
    }	

    t_target = find_living(lower_case(arg));
    target_room_file = environment(find_living(lower_case(arg)));    

    return ({ target_room_file, caster }); 
}

/*
 * Function:    query_teleport_ingredients
 * Description: This function defines what components are required for
 *              this haste spell.
 */
public string *
query_teleport_ingredients(object caster)
{
    return ({ "_aeria_component_" });
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
    
    // Not allowed to use on wizards
    if (t_target->query_wiz_level())
    {
        write("You cannot use this prayer on an immortal!\n");
        return 0;
    }

    // If they don't have the permission prop set, send them a request
    string TELEPORT_PROP = "_live_i_allow_ec_teleport_"+
        caster->query_real_name();
    if (!t_target->query_prop(TELEPORT_PROP))
    {
        // Check to see if they have a permission object and just haven't
        // responded yet
        if (present("_ec_teleport_permission_", t_target))
        {
            write(t_target->query_The_name(caster) + " hasn't responded to your "+
                "previous teleport request yet.\n");
            return 0;
        }
        // If they don't have the object, send them one requesting permission
        setuid(); 
        seteuid(getuid()); 
        object sphere = clone_object(ELEMENTALIST_SPELL_OBJS + 
            "ec_teleport_permission_obj");
        sphere->set_caster_name(caster);
        sphere->move(t_target,1);
        t_target->catch_msg("A small glowing sphere appears in your hands!\n"+
            "You feel the sphere is from " + QCNAME(caster) + " and it is a "+
            "request from " + caster->query_objective() + " to have "+
            "permission to teleport to you.\nIf you agree to allow "+
            caster->query_objective() + " to teleport to you, simply swallow "+
            "the sphere. If you do not grant " + caster->query_objective() +
            " to teleport to you, you may crush the sphere.\n");
        write("You have requested permission from "+(t_target->
            query_The_name(caster)) + " to teleport to them.\n");
        return 0;
    }
    
    // Check if they have permission prop set the and if it is not
    // set to 'yes' then don't let them spam the target with requests
    if (t_target->query_prop(TELEPORT_PROP) != "yes")
    {
        if (t_target)
        {
            write(t_target->query_The_name(caster) + " has denied you "+
                "permission to teleport to " + 
                t_target->query_objective() + ".\n");
        }
        return 0;
    }
        
    // They have the prop and it's set to 'yes' - do the actual teleport
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_PARADIDO)
    {
        return 0;
    }

    // Only master clerics and higher get this spell
    if (GUILD_MANAGER->query_is_child_cleric(player))
    {
        return 0;
    }
    
    // Only air clerics get this spell
    if (GUILD_MANAGER->query_primary_element(player) != "air")
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
            caster_message = "You bow your head in prayer to Lady Aeria "
                + "to carry you to your target.\n";
            watcher_message = QCTNAME(caster) + " bows " + 
            	caster->query_possessive()
                + " head in prayer.\n";
            break;
        
        case 1:
        default:
            caster_message = "You loudly chant the ancient "
                + "prayer of paradido to Lady Aeria, requesting passage by "
                + "air.\n";
            watcher_message = QCTNAME(caster) + " loudly chants an ancient "+
            	"prayer.\n";
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
 * Function:    resolve_teleport_spell
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
        caster->catch_tell("You cannot travel via paradido while you "+
        	"are in combat.\n");
    }
    else
    {
        caster->catch_tell("You lose your concentration of your "+
        	"paradido prayer as you are "
            + "distracted by combat.\n");
    }
}

/*
 * Function:    hook_cannot_teleport_caster_not_relaxed
 * Description: Hook that gets called when trying to teleport while having
 *              recently been in combat.
 *              This can get called both at the beginning and at the end of
 *              the spell casting. The "execute" variable determines whether
 *              it's all the beginning or the end.
 */
public void
hook_cannot_teleport_caster_not_relaxed(object caster, mixed * targets, string arg, int execute)
{
    caster->catch_tell("You have too recently been in combat. You have to "
        + "relax first before you can invoke the gift of paradido.\n");
}

/*
 * Function:    hook_cannot_teleport_caster_room_not_valid
 * Description: Hook that gets called when the caster's current room is not 
 *              valid. It
 *              can be valid for a number of reasons. See check_valid_action 
 *              for the
 *              conditions checked.
 */
public void
hook_cannot_teleport_caster_room_not_valid(object caster, mixed * targets, string arg, int execute, object caster_room)
{
    caster->catch_tell("The room you are in prevents you from magically "+
    	"departing.\n");
}

/*
 * Function:    hook_cannot_teleport_target_room_not_valid
 * Description: Hook that gets called when the spell's target room is not 
 *              valid. It
 *              can be valid for a number of reasons. See check_valid_action 
 *              for the
 *              conditions checked.
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
 *              to the same
 *              room that they are already in.
 */
public void             
hook_cannot_teleport_same_room(object caster, mixed * targets, string arg, int execute)
{
    caster->catch_tell("There's no need to call upon paradido. You're "+
    	"already there!\n");
}


/*
 * Function:    hook_describe_teleport_origin_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting out of the origin room.
 */
public void
hook_describe_teleport_origin_room(object caster, mixed *targets, object origin_room)
{
    caster->catch_tell("A whirlwind of air suddenly appears from above "
        + "and slides down your body until it engulfs you completely. As you "
        + "close your eyes, you feel yourself swirling around inside the "
        + "whirlwind.\n");
    tell_room(origin_room, "A whirlwind of air suddenly appears from "
        + "above and engulfs " + QTNAME(caster) + " completely. As "
        + "the whirlwind disappears above you, " + caster->query_pronoun()
        + " is gone.\n", ({ caster }) );
   
}

/*
 * Function:    hook_describe_teleport_target_room
 * Description: This is the hook that describes the action of caster
 *              successfully teleporting into the target room.
 */
public void
hook_describe_teleport_target_room(object caster, mixed *targets, object target_room)
{
    caster->catch_tell("Opening your eyes again, you find yourself "
        + "elsewhere.\n");
    tell_room(target_room, "A whirlwind of air suddenly appears out "+
        "of nowhere. It swirls around briefly before vanishing into "+
        "nothing, leaving " + QNAME(caster) + " in its place.\n",  
        ({ caster }) );
        // and remove the prop
    string TELEPORT_PROP = "_live_i_allow_ec_teleport_" +
        lower_case(caster->query_real_name());
    t_target->remove_prop(TELEPORT_PROP);

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
    return "aeria component (chicory, diamond shard)";
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
