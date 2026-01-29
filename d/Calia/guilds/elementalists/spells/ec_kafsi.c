/*
 * Kafsi mass harm spell for the Elemental Cleric Guild of Calia
 *
 * Created by Arman April 2022
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "massharm";
inherit (ELEMENTALIST_SPELLS + "spell_functions");


#define DEBUG(x)  find_player("arman")->catch_msg("[ec_kafsi] " + x + "\n")

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
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_massharm_spell()
{
    set_spell_name("kafsi");
    set_spell_desc("Poison your enemies with volcanic fumes");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_4);

    set_spell_combat_aid(60.0);
    set_spell_time_factor(2.5);
    set_spell_task(TASK_DIFFICULT);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");    

    /* Limit spell targets */
    set_spell_target_limit(3);

    set_spell_element(SS_ELEMENT_FIRE, 30);
    set_spell_form(SS_FORM_CONJURATION, 30);

    // Low component requirement with gem/herb charges
    set_spell_component_factor(COMPONENT_AID_LOW);
    
    set_spell_resist(spell_resist_poison);
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float result = 100.0;
    
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

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_massharm_ingredients(object caster)
{
    return ({ "_fire_component_" });
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_KAFSI)
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

    if (!caster_is_maintaining_skiamorfi_effects(caster))
    {
    	write("You must be in Elemental form to call upon the wrath of " +
            "Pyros!\n");
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

    caster_message = "Concentrating on the fires flowing through your " +
        "form you close your eyes briefly. Reaching deep within to the " +
        "primal fire, you call out to Lord Pyros and the wrath of flame.\n";
    watcher_message = QCTNAME(caster) + " closes " + caster->query_possessive() + 
        " eyes and concentrates briefly.\n";
        
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
			    caster->catch_tell("\n\nYou have acted outside of your "+
			    	"Vow of Service. "+
			        "This strains your connection with the Circle and "+
			        "the Conduit.\n\n\n");
	    		break;
	    	case 2:  // halved conduit gain, double conduit cost
	    		GUILD_MANAGER->add_practice_level(caster, 5);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 5);
			    GUILD_MANAGER->add_guild_conduit(5);
			    caster->catch_tell("\n\nYou have deliberately violated "+
			    	"your Vow of Service. "+
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
			    caster->catch_tell("\n\nYou have acted outside of your "+
			    	"Vow of Service. "+
			        "This strains your connection with the Circle and "+
			        "the Conduit.\n\n\n");
	    		break;
	    	case 2:  // halved conduit gain, double conduit cost
	    		GUILD_MANAGER->add_practice_level(caster, 2);
			    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
			    GUILD_MANAGER->add_guild_conduit(2);
			    caster->catch_tell("\n\nYou have deliberately violated "+
			    	"your Vow of Service. "+
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
        target_message = "You deftly avoid the toxic fumes and ash.\n";
        watcher_message = QCTNAME(target) + " deftly avoids the toxic " +
            "fumes and ash.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Toxic fumes and ash harmlessly surround you.\n";
            watcher_message = "Toxic fumes and ash harmlessly surround " + QTNAME(target)
                + ".\n";
            break;
            
        case 1..5:
            target_message = "Toxic gases and ash surround you, stinging you slightly.\n";
            watcher_message = "Toxic gases and ash surround " + QTNAME(target)
                + ", stinging " + target->query_objective() + " slightly.\n";
            break;
            
        case 6..10:
            target_message = "A maisma of hot toxic gases and ash surround you, mildly "
                + "blighting your " + hitloc_desc +  ".\n";
            watcher_message = "A maisma of hot toxic gases and ash surround " +QTPNAME(target) + 
                " " + hitloc_desc + ", mildly blighting " +target->query_objective()+ ".\n";
            break;

        case 11..25:
            target_message = "A violent blast of hot toxic gases and ash surrounds your " + 
                hitloc_desc + ", scourging you harshly.\n";
            watcher_message = "A violent blast of hot toxic gases and ash surround " +
                QTNAME(target) + ", scourging " +target->query_objective()+ " harshly.\n";
            break;
            
        case 26..35:
            target_message = "Writhing volcanic gases blast into you, harming you painfully.\n";
            watcher_message = "Writhing volcanic gases blasts into " +
                QTNAME(target) + ", harming " + target->query_objective()+ " painfully.\n";
            break;

        case 46..65:
            target_message = "Your " + hitloc_desc + " is engulfed in red-hot "
                + "poisonous gases and volcanic ash, causing severe damage.\n";
            watcher_message = QCTNAME(target) + " is engulfed in red-hot poisonous gases " +
                "and volcanic ash, causing severe damage.\n";
            break;

        case 66..85:
            target_message = "Roiling poisonous gases and volcanic ash wither your " +
                hitloc_desc+ ", causing grievous injuries.\n";
            watcher_message = "Roiling poisonous gases and volcanic ash wither " + 
                QTPNAME(target)+ " " + hitloc_desc + ", causing " +
                target->query_objective()+ " grievous injuries.\n";
            break;
     
        case 86..99:
            target_message = "Raging noxious gases and burning volcanic ash "
                +"fatally engulf you!\n";
            watcher_message = "Raging noxious gases and burning volcanic ash "+
                "fatally engulf "+ QTNAME(target) + "!\n";
            break;
            
        // Death (100% hurt or more)
        default:
            target_message = "A deadly torrent of hot noxious gases and molten " +
                "volcanic ash consume " +QTNAME(target)+ " completely!\n";
            watcher_message = "A deadly torrent of hot noxious gases and " +
                "molten volcanic ash consume " +QTNAME(target)+ " completely!\n";
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
    
    caster_message = "Your call is heard and a burning sensation alerts your " +
        "senses to your fires combusting and igniting the very air around " +
        "you, sending torrents of ash and toxic fumes in every direction!\n";
    target_message = QCTNAME(caster)+ " opens " + caster->query_possessive() +
        " eyes, flaming pure white, and " + caster->query_possessive() + 
        " fiery form gains a bluish hue as the very air around " + 
        caster->query_possessive() +" ignites in a violent combustion. " +
        "Torrents of ash and toxic fumes explode around " + 
        caster->query_possessive() + "!\n";
    watcher_message = QCTNAME(caster)+ " opens " + caster->query_possessive() +
        " eyes, flaming pure white, and " + caster->query_possessive() + 
        " fiery form gains a bluish hue as the very air around " + 
        caster->query_possessive() +" ignites in a violent combustion. " +
        "Torrents of ash and toxic fumes explode around " + 
        caster->query_possessive() + "!\n";        
    
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
    return "fire component (fireweed, golden pyrite shard)";
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


public void
hook_no_present_targets(object actor, string str)
{
    actor->catch_msg("You must first be in combat before you can call on "
    + "this prayer!\n");   
}