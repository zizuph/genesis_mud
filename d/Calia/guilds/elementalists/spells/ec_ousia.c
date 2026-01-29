/*
 * Essence Shatter At-Will Spell for the Elemental Cleric Guild of Calia
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
    set_spell_name("ousia");
    set_spell_desc("Shatter your enemies essence");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_combat_aid(20.0);
    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");    

    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_OUSIA)
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
    write("You feel ready to use the prayer of ousia again.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You do not feel ready to use the prayer of ousia again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are currently using the prayer of ousia!\n");
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
        caster_message = "You concentrate on the gifts of Spirit.\n";
        watcher_message = QCTNAME(caster) + " concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You concentrate on harnessing the blessings of "+
        	"Psuchae.\n";
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
			    caster->catch_tell("\n\nYou have acted outside of your Vow of "+
			    	"Service. "+
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
			    caster->catch_tell("\n\nYou have acted outside of your "+
			    	"Vow of Service. "+
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
        target_message = "A shadowy tendril flies past you, missing you "+
            "completely.\n";
        watcher_message = "A shadowy tendril flies past " + QTNAME(target) +
        	", missing "
            + target->query_objective()+ " completely.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A shadowy tendril flies into your "
                + hitloc_desc + " with no effect.\n";
            watcher_message = "A shadowy tendril flies into " + QTPNAME(target)
                + " " + hitloc_desc + " with no effect.\n";
            break;
            
        case 1..5:
            target_message = "A shadowy tendril shoots into your " +
            	hitloc_desc
                + " causing little discomfort.\n";
            watcher_message = "A shadowy tendril shoots into " + 
            	QTPNAME(target)
                + " " + hitloc_desc + " and causes little discomfort.\n";
            break;
            
        case 6..15:
            target_message = "A shadowy tendril shoots into your " + 
            	hitloc_desc
                + " causing some discomfort.\n";
            watcher_message = "A shadowy tendril shoots into " + 
            	QTPNAME(target)
                + " " + hitloc_desc + " and causes some discomfort.\n";
            break;
            
        case 16..25:
            target_message = "A radiant shadowy tendril shoots into your "
                + hitloc_desc + " and your "+hitloc_desc+" begins to flicker "+
                "and become translucent briefly. The experience is somewhat "+
                "painful.\n";
            watcher_message = "A radiant shadowy tendril shoots into " +
                QTPNAME(target) + " " + hitloc_desc + " and "+
                target->query_possessive()+
                " "+hitloc_desc+" begins to flicker and become translucent "+
                "briefly. The "+
                "experience seems to be somewhat painful to "+
                target->query_objective()+".\n";
            break;
            
        case 26..40:
            target_message = "A radiant shadowy tendril shoots into your "
                + hitloc_desc + " and your "+hitloc_desc+" begins to flicker "+
                "and become wholly translucent briefly. The experience is "+
                "very "+
                "painful.\n";
            watcher_message = "A radiant shadowy tendril shoots into " +
                QTPNAME(target) + " " + hitloc_desc + " and "+
                target->query_possessive()+
                " "+hitloc_desc+" begins to flicker and become wholly "+
                "translucent briefly. The "+
                "experience seems to be very painful to "+
                target->query_objective()+".\n";
            break;
       
        case 41..65:
            target_message = "Tendrils of pulsating shadows emerge all "+
            	"around "+
                "you. As the tendrils shift and drive through your "+
                hitloc_desc + " violently, your "+hitloc_desc+" begins to "+
                "drain and "+
                "flicker out of existence. As the "+hitloc_desc+
                " solidifies again, you "+
                "are left drained and wracked.\n";
            watcher_message = "Tendrils of pulsating shadows emerge "+
            	"all around " +
                QTNAME(target) + ". As the tendrils shift and drive through "+
                target->query_possessive()+ " " + hitloc_desc + " violently, "+
                target->query_possessive()+ " " + hitloc_desc + " begins "+
                "to drain and "+
                "flicker out of existence. As the " + hitloc_desc + 
                " solidifies again, "+
                target->query_pronoun() + " is left drained and wracked.\n";
            break;

        case 66..99:
            target_message = "You are wrapped in a blanket of sparking "+
            	"shadowy "+
                "tendrils. With a twirl your " + hitloc_desc + " and then "+
                "your whole "+
                "form are shadow wrought. A zapping sensation alerts you to "+
                "your entire "+
                "body flickering rapidly, as if existence itself was being "+
                "drained from "+
                "you.\n";
            watcher_message = QCTNAME(target) + " is wrapped in a blanket "+
            	"of sparking shadowy "+
                "tendrils. With a twirl " + target->query_possessive() + 
                " " + hitloc_desc +
                " and then " + target->query_possessive() + " whole form "+
                "are shadow wrought. "+
                "A zapping sensation alerts you to " + QTPNAME(target) + 
                " entire "+
                "body flickering rapidly, as if existence itself was being "+
                "drained from "+
                target->query_objective() + ".\n";
            break;

        default:
            target_message = "Roaring tendrils of shadow coalesce and "+
            	"emerge from the "+
                "corner of your eye. With amazing speed they drive towards "+
                "you and penetrate "+
                "your " + hitloc_desc + ", flowing through you, striking "+
                "towards your center. "+
                "They leave only pain as they again escape upwards, trailing "+
                "a shadowy void. "+
                "The succumbing drain is the last moan of pain you feel "+
                "before joining with "+
                "void, becoming naught.\n";
            watcher_message = "Roaring tendrils of shadow coalesce and "+
            	"emerge from the "+
                "corner of your eye. With amazing speed they drive towards "+
                QTNAME(target) +
                " and penetrate " + target->query_possessive() + " " +
                hitloc_desc + ", flowing "+
                "through " + target->query_objective() + ", striking towards "+
                target->query_possessive() + " center. They appear to leave "+
                "only pain as they "+
                "again escape upwards, trailing a shadowy void. A drained "+
                "moan escapes "+
                QTNAME(target) + " before " + target->query_pronoun() + 
                " becomes naught.\n";
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
        caster_message = "Shadowy tendrils form on the tips of your fingers "+
        	"and you "+
            "direct them towards " + QTNAME(target) + ".\n";
        target_message = "Shadowy tendrils form on the tips of " + 
        	QTPNAME(caster) + "fingers and " +
            caster->query_pronoun() + " directs them towards you.\n";
        watcher_message = "Shadowy tendrils form on the tips of " + 
        	QTPNAME(caster) + " fingers and " + 
            caster->query_pronoun() + " directs them towards "
            + QTNAME(target) + ".\n";
        break;
        
    case 1:
    default:
        caster_message = "A swirl of shadow and light form tendrils at "+
        	"your fingertips and you push "
            + "them towards " + QTNAME(target) + ".\n";
        target_message = "A swirl of shadow and light form tendrils at " +
        	QTPNAME(caster) + 
            " fingertips and " + caster->query_pronoun() + " pushes them "+
            "towards you.\n";
        watcher_message = "A swirl of shadow and light form tendrils at " +
        	QTPNAME(caster) + 
            " fingertips and " + caster->query_pronoun() + " pushes them "+
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
