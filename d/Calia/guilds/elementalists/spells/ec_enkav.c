/*
 * Burn At-Will Spell for the Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, January 2017
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "at_will_harm";
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
    set_spell_name("enkav");
    set_spell_desc("Burn your enemies with tendrils of fire");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_combat_aid(60.0);
    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");    

    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_FIRE));
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_ENKAV)
    {
        return 0;
    }

    // Only master clerics and higher get this spell
    if (GUILD_MANAGER->query_is_child_cleric(player))
    {
        return 0;
    }
    
    // Only fire clerics get this spell
    if (GUILD_MANAGER->query_primary_element(player) != "fire")
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
    write("You feel ready to use the prayer of enkav again.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You do not feel ready to use the prayer of enkav again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are currently using the prayer of enkav!\n");
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
        caster_message = "You hold out your palm with the fingers pointed "
            + "away from you and focus on gathering the power of the "
            + "heat in the air.\n";
        watcher_message = QCTNAME(caster) + " holds out "
            + caster->query_possessive() + " palm and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You summon your inner reserves of power and "
            + "focus your mind on utilizing the element of fire.\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and concentrates.\n";
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
			        "of Service. This strains your connection with the "+
			        "Circle and the Conduit.\n\n\n");
	    		break;
	    	case 2:  // halved conduit gain, double conduit cost
	    		GUILD_MANAGER->add_practice_level(caster, 5);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
			    GUILD_MANAGER->add_guild_conduit(5);
			    caster->catch_tell("\n\nYou have deliberately violated "+
			        "your Vow of Service. The Conduit between the Circle "+
			        "and the Five suffers from your lack of Faith.\n\n\n");
	    		break;
	    	case 3:  // halved conduit gain, double conduit cost, halved CAID
	    		GUILD_MANAGER->add_practice_level(caster, 5);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
			    GUILD_MANAGER->add_guild_conduit(5);
			    caster->catch_tell("\n\nYou have repeatedly violated your "+
			        "Vow of Service. With such malpractice, your prayers "+
			        "sound weak and hollow.\n\n\n");
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
			    caster->catch_tell("\n\nYou have acted outside of your "+
			        "Vow of Service. This strains your connection with "+
			        "the Circle and the Conduit.\n\n\n");
	    		break;
	    	case 2:  // halved conduit gain, double conduit cost
	    		GUILD_MANAGER->add_practice_level(caster, 2);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
			    GUILD_MANAGER->add_guild_conduit(2);
			    caster->catch_tell("\n\nYou have deliberately violated "+
			        "your Vow of Service. The Conduit between the Circle "+
			        "and the Five suffers from your lack of Faith.\n\n\n");
	    		break;
	    	case 3:  // halved conduit gain, double conduit cost, halved CAID
	    		GUILD_MANAGER->add_practice_level(caster, 2);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
			    GUILD_MANAGER->add_guild_conduit(2);
			    caster->catch_tell("\n\nYou have repeatedly violated your "+
			        "Vow of Service. With such malpractice, your prayers "+
			        "sound weak and hollow.\n\n\n");
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
        target_message = "Fire tendrils fly towards you with great speed, "+
            "but at the last moment you are able to move aside and dodge "+
            "them, escaping unscathed.\n";
        watcher_message = "Fire tendrils fly towards " + QTNAME(target)+
            " with great speed, but at the last moment "+
            target->query_pronoun() + " is able to move aside and dodge "+
            "them, escaping unscathed.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Swirling fiery tendrils strike you on the "
                + hitloc_desc + " and barely hurts you.\n";
            watcher_message = "Swirling fiery tendrils strike " 
                + QTNAME(target)
                + " on the " + hitloc_desc + " and barely hurts "
                + target->query_objective() + ".\n";
            break;
            
        case 1..5:
            target_message = "Fiery tendrils dig deeply into your " 
                + hitloc_desc
                + " and cause you to bleed.\n";
            watcher_message = "Fiery tendrils dig deeply into " 
                + QTPNAME(target)
                + " " + hitloc_desc + " and cause " + target->query_objective()
                + " to bleed.\n";
            break;
            
        case 6..15:
            target_message = "You turn your body to try and dodge the "
                + "many fiery "
                + "tendrils hurtling towards you, but are unable to keep "
                + "them from "
                + "burning your " + hitloc_desc + ".\n";
            watcher_message = QCTNAME(target) + " turns " 
                + target->query_possessive() + " body to try and dodge "
                + "the many "
                + "fiery tendrils hurtling towards " + target->query_objective()
                + ", but " + target->query_pronoun() + " is unable to "
                + "keep them "
                + "from burning " + target->query_possessive() + " "
                + hitloc_desc + ".\n";
            break;
            
        case 16..25:
            target_message = "White fiery tendrils strike you and break upon "
                + "contact into burning sparks, searing you on your "
                + hitloc_desc + " and causing many wounds.\n";
            watcher_message = "White fiery tendrils strike " 
                + QTNAME(target) + " and "
                + "break upon contact into burning sparks, searing "
                + target->query_objective() + " on " 
                + target->query_possessive()
                + " " + hitloc_desc + " and causing many wounds.\n";
            break;
            
        case 26..40:
            target_message = "Flying past you at tremendous speeds, the "
                + "fiery tendrils "
                + "seem to miss you, but at the last moment they come "
                + "hurtling "
                + "back and wrap your " + hitloc_desc + ", burning you "
                + "deeply.\n";
            watcher_message = "Flying past " + target->query_objective() 
                + " at "
                + "tremendous speeds, the fiery tendrils seem to miss " 
                + target->query_objective() + ", but at the last moment "
                + "they come "
                + "hurtling back and wrap " + target->query_possessive()
                + " " + hitloc_desc + ", burning " + target->query_objective() 
                + " deeply.\n";
            break;
                   
        case 41..65:
            target_message = "A streak of fire hurtles towards you, splits "
                + "into dozens of fiery tendrils, wraps your "
                + hitloc_desc + " until it forms again into a sheet of "
                + "burning fire that burns you deeply, forcing you to your "
                + "knees in pain.\n";
            watcher_message = "A streak of fire hurtles towards " 
                + QTNAME(target)
                + ", splits into dozens of fiery tendrils, wraps "
                + target->query_possessive() + " " + hitloc_desc 
                + " until it "
                + "forms again into a sheet of burning fire that burns "
                + target->query_objective() + " deeply, forcing "
                + target->query_objective() + " to " 
                + target->query_possessive()
                + " knees in pain.\n";
            break;

        case 66..99:
            target_message = "The impact of the fiery tendrils striking your "
                + hitloc_desc + " is so great, and the heat from the fire so "
                + "incendiary, that you only momentarily feel the pain "
                + "before it burns away your nerves and boils your blood.\n";
            watcher_message = "The impact of the fiery tendrils striking "
                + QTNAME(target) + " is so great, and the heat from the fire "
                + "so incendiary, that " + target->query_pronoun() + " only "
                + "briefly feels pain until it burns away " 
                + target->query_possessive()
                + " nerves and boils " + target->query_possessive() 
                + " blood.\n";
            break;
            
        default:
            target_message = "Hundreds of fiery tendrils explode into sight "
                + "and pummel you on your " + hitloc_desc + ", digging into "
                + "your body and exploding from within, causing your blood "
                + "to boil out of your body with excruciating pain.\n";
            watcher_message = "Hundreds of fiery tendrils explode into sight "
                + "and pummel " + QTNAME(target) + " on " 
                + target->query_possessive()
                + " " + hitloc_desc + ", digging into " 
                + target->query_possessive()
                + " body and exploding from within, causing the blood to boil "
                + "out of the body with excruciating pain.\n";
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
        caster_message = "Fire begins to form at your fingertips and "
            + "gradually grows into fiery tendrils. You direct them towards "
            + QTNAME(target) + ".\n";
        target_message = "Fiery tendrils form at " + QPNAME(caster) 
            + " fingertips "
            + "as " + caster->query_pronoun() + " pushes out "
            + caster->query_possessive() + " palm towards you.\n";
        watcher_message = "Fiery tendrils form at " + QTPNAME(caster) 
            + " fingertips "
            + "as " + caster->query_pronoun() + " pushes out "
            + caster->query_possessive() + " palm towards "
            + QTNAME(target) + ".\n";
        break;
        
    case 1:
    default:
        caster_message = "White and yellow energies swirl around your "
            + "outstretched palm and form into fiery tendrils. You push "
            + "them towards " + QTNAME(target) + ".\n";
        target_message = "White and yellow energies swirl around the "
            + "outstretched palm of " + QTNAME(caster) + " as "
            + caster->query_pronoun() + " pushes out the fiery tendrils "
            + "towards you.\n";
        watcher_message = "White and yellow energies swirl around the "
            + "outstretched palm of " + QTNAME(caster) + " as "
            + caster->query_pronoun() + " pushes out the fiery tendrils "
            + "towards " + QTNAME(target) + ".\n";        
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
