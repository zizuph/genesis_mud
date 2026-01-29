/*
 * Essence Drain Spell for the Elemental Cleric Guild of Calia
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
inherit SPELL_DIR + "harm";
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
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_harm_spell()
{
    set_spell_name("diochetevo");
    set_spell_desc("Drain your enemies essence");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_4);

    // Low component requirement
    set_spell_component_factor(COMPONENT_AID_LOW);

    set_spell_combat_aid(20.0);
    set_spell_time_factor(2.5);
    set_spell_task(TASK_HARD); 
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");   

    set_spell_element(SS_ELEMENT_LIFE, 30);
    set_spell_form(SS_FORM_CONJURATION, 30);
    
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_LIFE));
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
    
    // Has guru quest been completed? If so, set at 45, otherwise 30
    if (this_player()->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
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
    return ({ "_spirit_component_" });
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


    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_ONKOLITHOS)
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
        caster_message = "You hold out your hand with the fingers pointed "
            + "away from you and focus on gathering the power of Psuchae.\n";
        watcher_message = QCTNAME(caster) + " holds out "
            + caster->query_possessive() + " hand and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You summon your inner reserves of power and "
            + "focus your mind on utilizing the element of spirit.\n";
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
			    caster->catch_tell("\n\nYou have acted outside of your "+
			        "Vow of Service. This strains your connection with "+
			        "the Circle and the Conduit.\n\n\n");
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
			    caster->catch_tell("\n\nYou have deliberately violated your "+
			        "Vow of Service. The Conduit between the Circle and the "+
			        "Five suffers from your lack of Faith.\n\n\n");
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
        target_message = "You feel something intangible fly past you and "+
            "barely miss you.\n";
        watcher_message = "Something intangible flies past " + QTNAME(target)+
            " barely missing " + target->query_objective()+ ".\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Something intangible strikes your "
                + hitloc_desc + " with no discomfort.\n";
            watcher_message = "Something intangible strikes "+
                QTPNAME(target) + " " + hitloc_desc + " with no "+
                "discomfort.\n";
            break;
            
        case 1..10:
            target_message = "A small mass of shadow and light strikes your "+
                hitloc_desc + " causing only minor discomfort.\n";
            watcher_message = "A small mass of shadow and light strikes "+
                QTPNAME(target) + " " + hitloc_desc + " causing only minor "+
                "discomfort.\n";
            break;
            
        case 11..25:
            target_message = "As the mass of shadow and light impacts your "+
                hitloc_desc + " and you feel a strong discomfort from "+
                "within.\n";
            watcher_message = "As the mass of shadow and light impacts "+
                QTPNAME(target) + " " + hitloc_desc + ", "+
                target->query_pronoun() + " looks very uncomfortable.\n";
            break;
            
        case 26..40:
            target_message = "A ball of shadows sparkled with light "+
                "swiftly strikes your " + hitloc_desc + " and as it enters "+
                "you, you feel a drain of cohesion causing wounds to "+
                "suddenly erupt all over you.\n";
            watcher_message = "A ball of shadows sparkled with light "+
                "swiftly strikes " + QTPNAME(target) + " " + hitloc_desc+
                ". As it enters " + target->query_objective() + ", they "+
                "appear to be drained of energy and wounds erupt all over "+
                target->query_possessive()+" body.\n";
            break;
            
        case 41..65:
            target_message = "A large mass of shadowy engulfed light "+
                "strikes your " + hitloc_desc + " with a terrible "+
                "sensation that spreads throughout your body. For a "+
                "stumbling moment raw agony is all you feel, as your "+
                "cohesion briefly falters leaving painful wounds in its "+
                "draining wake.\n";
            watcher_message = "A large mass of shadowy engulfed light "+
                "strikes " + QTPNAME(target) + " " + hitloc_desc + " and "+
                target->query_pronoun()+ " stumbles as cohesion itself "+
                "seems to falter from within " + target->query_objective()+
                ", leaving painful wounds in its draining wake.\n";
            break;
     
        case 66..99:
            target_message = "The shadow mass radiates violently as it "+
                "penetrates your " + hitloc_desc + ". Your vision blurs "+
                "and your surroundings fades from sight as your world "+
                "becomes horrible pain. Everything that holds you "+
                "together seems to tear and drain away briefly. Your body "+
                "is left in tormented wounded ruin by the wrecking drain "+
                "of cohesion.\n";
            watcher_message = "The shadow mass radiates violently as it "+
                "penetrates " + QTPNAME(target) + " " + hitloc_desc + ". "+
                capitalize(target->query_pronoun()) + " seems lost in "+
                "horrible pain as sparks of purest light and darkest shadow "+
                "seems to erupt from within " + target->query_possessive()+
                " body. For a moment everything that holds " + QTNAME(target)+
                " together seems to tear and drain away briefly. "+
                capitalize(target->query_possessive()) + " body "+
                "is left in tormented wounded ruin by the wrecking drain "+
                "of cohesion.\n";
            break;
            
        // Death (100% hurt or more)
        default:
            target_message = "A radiant shadowy mass quickly burrows into "+
                "your " + hitloc_desc + " and paralyzing pain explodes from "+
                "the impact. You feel every ounce of your body being drained "+
                "and torn apart from within itself. A flash of blinding "+
                "light is your last experience as utter and complete "+
                "incohesion disintegrates you from within.\n";
            watcher_message = "A radiant shadowy mass quickly burrows into "+
                QTNAME(target) + " " + hitloc_desc + ", for a moment "+
                target->query_pronoun() + " is completely still in a "+
                "moment of paralyzing pain. A briefly surprised "+
                "expression is followed by cracks of light and shadow "+
                "opening all over " + target->query_objective() + ". "+
                "Every ounce of " + target->query_possessive()+
                " body seems to be being torn apart. A flash of blinding "+
                "light engulfs " + target->query_objective()+
                " as utter and complete incohesion disentegrates "+
                target->query_objective() + " from within.\n";
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
        caster_message = "Shadow and light begins to form at your "+
            "fingertips and you stretch your hand towards "+
            QTNAME(target) + ".\n";
        target_message = "Shadow and light forms at " + QPNAME(caster)+
            " fingertips as " + caster->query_pronoun() + " stretches "
            + caster->query_possessive() + " hand towards you.\n";
        watcher_message = "Shadow and light forms at " + QTPNAME(caster)+
            " fingertips as " + caster->query_pronoun() + " stretches "
            + caster->query_possessive() + " hand towards "
            + QTNAME(target) + ".\n";
        break;
        
    case 1:
    default:
        caster_message = "Shadow and light forms a shadowy mass in "
            + "the palm of your hand. You direct "
            + "it towards " + QTNAME(target) + ".\n";
        target_message = "Shadow and light form a shadowy mass in "
            + "the palm of " + QTPNAME(caster) + " hand as "
            + caster->query_pronoun() + " directs it "
            + "towards you.\n";
        watcher_message = "Shadow and light form a shadowy mass in "
            + "the palm of " + QTPNAME(caster) + " hand as "
            + caster->query_pronoun() + " directs it "
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
    return "spirit component (drakeroot, onyx shard)";
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
