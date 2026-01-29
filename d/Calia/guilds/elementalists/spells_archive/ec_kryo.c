/*
 * Frostbite At-Will Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, January 2017
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/at_will_harm";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

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
 * Function:    config_at_will_spell
 * Description: Config function for at will damage spells. Redefine this in your
 *              own at will spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_at_will_spell()
{
    set_spell_name("kryo");
    set_spell_desc("Strike your enemies with frostbite");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(60.0);
    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");    

    set_spell_element(SS_ELEMENT_WATER, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_COLD));
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */

public float
query_spell_combat_aid_modifier()
{
    float result;
    
    // Has guru quest been completed? If so, set at 60, otherwise 45
    if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    {
    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
    		result = 50.0;
    	else
        	result = 100.0;
        	
        return result;
    }

    if (TP->query_prop(CONDUIT_PENALTY) == 3)
   		result = 37.5;
    else
    	result = 75.0;
    	
    return result;
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({  });
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_KRYO)
    {
        return 0;
    }

    // Only master clerics and higher get this spell
    if (GUILD_MANAGER->query_is_child_cleric(player))
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

// HOOKS TO BE DEFINED

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their at will spell again.
 */
public void 
hook_special_complete()
{
    write("You feel ready to use the prayer of kryo again.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You do not feel ready to use the prayer of kryo again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are currently using the prayer of kryo!\n");
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
    switch (random(2))
    {
    case 0:
        caster_message = "You concentrate on the gifts of Water.\n";
        watcher_message = QCTNAME(caster) + " concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You concentrate on harnessing the blessings of "+
            "Lord Diabrecho.\n";
        watcher_message = QCTNAME(caster) + " concentrates.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
    int conduit_penalty = caster->query_prop(CONDUIT_PENALTY);
    
    // Master Guru Cleric Conduit
    if (caster->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    {
        switch(conduit_penalty)
	    {
	    	case 1:  // halved conduit gain
	    		GUILD_MANAGER->add_practice_level(caster, 5);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
			    GUILD_MANAGER->add_guild_conduit(5);
			    caster->catch_tell("\n\nYou have acted outside of your Vow "+
			        "of Service. "+
			        "This strains your connection with the Circle and the "+
			        "Conduit.\n\n\n");
	    		break;
	    	case 2:  // halved conduit gain, double conduit cost
	    		GUILD_MANAGER->add_practice_level(caster, 5);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
			    GUILD_MANAGER->add_guild_conduit(5);
			    caster->catch_tell("\n\nYou have deliberately violated your "+
			        "Vow of Service. "+
			        "The Conduit between the Circle and the Five suffers "+
			        "from your lack of Faith.\n\n\n");
	    		break;
	    	case 3:  // halved conduit gain, double conduit cost, halved CAID
	    		GUILD_MANAGER->add_practice_level(caster, 5);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
			    GUILD_MANAGER->add_guild_conduit(5);
			    caster->catch_tell("\n\nYou have repeatedly violated your "+
			        "Vow of Service. "+
			        "With such malpractice, your prayers sound weak and "+
			        "hollow.\n\n\n");
	    		break;
	    	default:
	    		GUILD_MANAGER->add_practice_level(caster, 10);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 10);
			    GUILD_MANAGER->add_guild_conduit(10);
	    		break;
	    }
    }
    else
    {
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
			        "The Conduit between the Circle and the Five suffers "+
			        "from your lack of Faith.\n\n\n");
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
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from harm's hit_me.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A mass of vaporized cold water surges past you, "+
            "missing you completely.\n";
        watcher_message = "A mass of vaporized cold water surges past " +
            QTNAME(target) + ", missing " + target->query_objective()+
            " completely.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A mass of vaporized cold water flies into your "
                + hitloc_desc + " with no effect.\n";
            watcher_message = "A mass of vaporized cold water flies into " +
                QTPNAME(target)+ " " + hitloc_desc + " with no effect.\n";
            break;
            
        case 1..5:
            target_message = "A mass of vaporized cold water flies into your "+
                hitloc_desc + " chilling it briefly.\n";
            watcher_message = "A mass of vaporized cold water flies into " +
                QTPNAME(target) + " " + hitloc_desc + " chilling " + 
                target->query_objective()
                + " briefly.\n";
            break;
            
        case 6..15:
            target_message = "A mass of vaporized cold water flies into your "+
                hitloc_desc + " chilling it somewhat.\n";
            watcher_message = "A mass of vaporized cold water flies into " +
                QTPNAME(target) + " " + hitloc_desc + " chilling " + 
                target->query_objective()
                + " somewhat.\n";
            break;
            
        case 16..25:
            target_message = "A very cold mass of vaporized water flies into "+
                "your "
                + hitloc_desc + " numbing it.\n";
            watcher_message = "A very cold mass of vaporized cold water "+
                "flies into " +
                QTPNAME(target) + " " + hitloc_desc + " numbing " + 
                target->query_objective()
                + ".\n";
            break;
            
        case 26..40:
            target_message = "A very cold mass of vaporized water flies "+
                "into your "
                + hitloc_desc + " numbing it painfully.\n";
            watcher_message = "A very cold mass of vaporized cold water "+
                "flies into " +
                QTPNAME(target) + " " + hitloc_desc + " numbing " + 
                target->query_objective()
                + " painfully.\n";
            break;
       
        case 41..65:
            target_message = "A large freezing mass of vaporized water "+
                "flies into your "
                + hitloc_desc + " forcing you to your knees in pain "+
                "briefly.\n";
            watcher_message = "A large freezing mass of vaporized water "+
                "flies into " +
                QTPNAME(target) + " " + hitloc_desc + " and causes " + 
                target->query_objective()
                + " to drop to "+ target->query_possessive() + " knees in "+
                "pain briefly.\n";
            break;

        case 66..99:
            target_message = "A boreal mass of vaporized water has wrapped "+
                "itself "+
                "around you and a raw biting cold erupts from your "+
                hitloc_desc + ". Arctic streaks of numbing pain is left "+
                "in the wake "+
                "of the gruesome frostbite covering you from head to toe.\n";
            watcher_message = "A boreal mass of vaporized water has wrapped "+
                "itself "+
                "around " + QTNAME(target) + " and a raw biting cold erupts "+
                "from " +
                target->query_possessive() + " " + hitloc_desc+". Gruesome "+
                "frostbite "+
                "covers "+target->query_objective()+" from head to toe.\n";
            break;

        default:
            target_message = "A biting sensation of intense cold explodes "+
                "from your " +
                hitloc_desc + ". Undercooled water suddenly runs all over "+
                "you and "+
                "encases you in an icy tomb of glaciate death. As the water "+
                "rapidly "+
                "seeps away into nothingness, so does your frostbitten "+
                "ruined life.\n";
            watcher_message = "A biting sensation of intense cold explodes "+
                "from " +
                QTPNAME(target) + " " + hitloc_desc + ". Undercooled water "+
                "suddenly "+
                "runs all over " + target->query_objective() + " and encases "+
                target->query_objective() + " in an icy tomb of glaciate "+
                "death. As the "+
                "water rapidly seeps away into nothingness, so does "+
                target->query_possessive()+" frostbitten ruined life.\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object * targets)
{
    string caster_message, target_message, watcher_message;
    object target;
    
    target = targets[0];
    
    switch (random(2))
    {
    case 0:
        caster_message = "Frost forms at your fingertips and you direct it "+
            "towards "
            + QTNAME(target) + ".\n";
        target_message = "Frost forms on " + QTPNAME(caster) + " fingertips "+
            "and " +
            caster->query_pronoun() + " directs it towards you.\n";
        watcher_message = "Frost forms on " + QTPNAME(caster) + " fingertips "+
            "and " + 
            caster->query_pronoun() + " directs it towards "
            + QTNAME(target) + ".\n";
        break;
        
    case 1:
    default:
        caster_message = "Small shards of ice form on your fingertips and "+
            "you push "
            + "them towards " + QTNAME(target) + ".\n";
        target_message = "Small shards of ice form on " + QTPNAME(caster) + 
            " fingertips and " + caster->query_pronoun() + " pushes them "+
            "towards you.\n";
        watcher_message = "Small shards of ice form on " + QTPNAME(caster) + 
            " fingertips and " + caster->query_pronoun() + " pushes them "+
            "towards " +
            QTNAME(target) + ".\n";        
    }
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);    
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
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
    write("You need a proper ritual component to generate "
        + "the manifestation of " + query_spell_name() + ".\n");
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
