/*
 * Earthen Shards At-Will Spell for the Elemental Cleric Guild of Calia
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
    set_spell_name("oxy");
    set_spell_desc("Strike your enemies with earthen shards");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_combat_aid(30.0);
    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");    

    set_spell_element(SS_ELEMENT_EARTH, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_EARTH));
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
    
    // Has guru quest been completed? If so, set at 30, otherwise 20
    if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    {
    	if (TP->query_prop(CONDUIT_PENALTY) == 3)
    		result = 50.0;
    	else
        	result = 100.0;
        return result;
    }

    if (TP->query_prop(CONDUIT_PENALTY) == 3)
    	result = 33.4;
    else
    	result = 66.7;
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_OXY)
    {
        return 0;
    }

    // Only master clerics and higher get this spell
    if (GUILD_MANAGER->query_is_child_cleric(player))
    {
        return 0;
    }
    
    // Only earth clerics get this spell
    if (GUILD_MANAGER->query_primary_element(player) != "earth")
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
    write("You feel ready to use the prayer of oxy again.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You do not feel ready to use the prayer of oxy again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are currently using the prayer of oxy!\n");
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
        caster_message = "You concentrate on the gifts of the Earth.\n";
        watcher_message = QCTNAME(caster) + " concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You concentrate on harnessing the blessings of "+
        	"Lady Gu.\n";
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
        target_message = "Razor sharp earthen shards hurl past you, leaving "+
            "you unharmed.\n";
        watcher_message = "Razor sharp earthen shards hurl past " + 
        	QTNAME(target) +
            " leaving " + target->query_objective()+ " unharmed.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A few earthen shards fly into your "
                + hitloc_desc + " with little effect and fall to the ground, "+
                "shattering on impact.\n";
            watcher_message = "A few earthen shards fly into " + 
            	QTPNAME(target)
                + " " + hitloc_desc + " with little effect and fall to "+
                "the ground, "+
                "shattering on impact.\n";
            break;
            
        case 1..5:
            target_message = "Several earthen shards fly into your " + 
            	hitloc_desc
                + " grazing you somewhat.\n";
            watcher_message = "Several earthen shards fly into " + 
            	QTPNAME(target)
                + " " + hitloc_desc + " grazing " + target->query_objective()
                + " somewhat.\n";
            break;
            
        case 6..15:
            target_message = "Many earthen shards fly into your " + 
            	hitloc_desc +
                " hurting you somewhat.\n";
            watcher_message = "Many earthen shards fly into " + 
            	QTPNAME(target)
                + " " + hitloc_desc + " hurting " + target->query_objective()
                + " somewhat.\n";
            break;
            
        case 16..25:
            target_message = "Sharp shards of earth fly towards you and "+
            	"slice "+
                "effectively into your "+ hitloc_desc + " causing you "+
                "sharp pain.\n";
            watcher_message = "Sharp shards of earth fly towards " + 
            	QTNAME(target) + 
                " and slice effectively into " + target->query_possessive()
                + " " + hitloc_desc + " and causing sharp pain.\n";
            break;
            
        case 26..40:
            target_message = "Pointed edges and spikes glitter as they "+
            	"fly towards "+
                "you, massive spikes of earthen shards shred your " + 
                hitloc_desc +
                ", hurting you deeply.\n";
            watcher_message = "Pointed edges and spikes glitter as they "+
            	"fly towards " +
                QTNAME(target)+", massive spikes of earth shards shread "+
                target->query_possessive()+ " " + hitloc_desc + ", hurting " +
                target->query_objective() + " deeply.\n";
            break;
       
        case 41..65:
            target_message = "Pointed edges and spikes glittering with "+
            	"deadly "+
                "promise fly towards you, massive spikes of earthen shards "+
                "maul "+
                "your " + hitloc_desc + " horribly, forcing you to your "+
                "knees in "+
                "pain briefly.\n";
            watcher_message = "Pointed edges and spikes glittering with "+
            	"deadly "+
                "promise fly towards " + QTNAME(target)+ ", massive spikes "+
                "of earthen "+
                "shards maul "+target->query_possessive()+ " " + hitloc_desc +
                " horribly, forcing " + target->query_objective()
                + " to drop to "+ target->query_possessive() + " knees in "+
                "pain briefly.\n";
            break;

        case 66..99:
            target_message = "Full of deadly speed and precision, massive "+
            	"razors "+
                "of sharpened earth pound into your " + hitloc_desc + 
                " slicing "+
                "you open as they leave your "+hitloc_desc+" a mangled "+
                "piece.\n";
            watcher_message = "Full of deadly speed and precision, massive "+
            	"razors "+
                "of sharpened earth pound into " + QTPNAME(target) + " " +
                hitloc_desc+
                "slicing "+target->query_objective()+" open as they leave "+
                target->query_possessive()+" " + hitloc_desc+" a mangled "+
                "piece.\n";
            break;

        default:
            target_message = "A vortex of earthen death lays upon you. "+
            	"Massive shards "+
                "of earth surround you in a twirling and slicing reckoning "+
                "of continued "+
                "pain, leaving a trail of countless wounds in its wake. "+
                "One shard after "+
                "another burrows deeply within you, only to painfully "+
                "emerge with a scrap "+
                "of form and life, until at last you fall to the ground "+
                "in a bloody and "+
                "shredded heap.\n";
            watcher_message = "A vortex of earthen death lays upon " + 
            	QTNAME(target) + ". " +
                "Massive shards of earth surround "+target->query_objective()+
                " in a twirling "+
                "and slicing reckoning of continued pain, leaving a trail "+
                "of countless wounds "+
                "in its wake. One shard after another burrows deeply within "+
                target->query_objective()+", only to painfully emerge with "+
                "a scrap "+
                "of form and life, until at last "+target->query_pronoun()+
                " falls to the ground "+
                "in a bloody and shredded heap.\n";
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
        caster_message = "Particles of earth begin to form at your "+
           "fingertips. You direct them towards " + QTNAME(target) + ".\n";
        target_message = "Particles of earth begin to form on the "+
            "fingertips of " + QPNAME(caster) + " and " +
            caster->query_pronoun() + " directs them towards you.\n";
        watcher_message = "Particles of earth being to form on the "+
            "fingertips of " + QTPNAME(caster) + " and " + 
            caster->query_pronoun() + " directs them towards "
            + QTNAME(target) + ".\n";
        break;
        
    case 1:
    default:
        caster_message = "Dirt and debris swirl around your hands forming "+
            "shards. You quickly direct them towards " + QTNAME(target) + 
            ".\n";
        target_message = "Dirt and debris swirl around " + QTPNAME(caster) + 
            " hands and " + caster->query_pronoun() + " quickly directs them "+
            "towards you.\n";
        watcher_message = "Dirt and debris swirld around " + QTPNAME(caster) + 
            " hands and " + caster->query_pronoun() + " quickly directs them "+
            "towards " + QTNAME(target) + ".\n";        
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
