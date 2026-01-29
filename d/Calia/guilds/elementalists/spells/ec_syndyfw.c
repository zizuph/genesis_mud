/*
 * Syndyasmos Fire + Water combination spell the 
 * Elemental Cleric Guild of Calia
 *
 * Created by Jaacar, June 2017
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

/*
 * Function:    is_full_master_cleric_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_full_master_cleric_spell()
{
    return 1;
}

/*
 * Function:    config_massharm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_massharm_spell()
{
    set_spell_name("nerofotias");
    set_spell_desc("Syndyasmos Fire + Water Combination");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_fail("Your prayer fails.\n");
    set_spell_combat_aid(130.0);
    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    // 2.0 times the standard cast time for a harm spell 
    set_spell_time_factor(2.0); 
  
    set_spell_element(SS_ELEMENT_FIRE, 50);
    set_spell_form(SS_FORM_CONJURATION, 50);

    set_spell_target_limit(3);
    set_spell_restrict_targets(6);

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
    float caid_result;
    
    if (TP->is_elemental_racial_cleric)
    {
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
    		caid_result = 50.0;
    	else
    		caid_result = 100.0;
    }
    else
    {
        if (TP->query_prop(CONDUIT_PENALTY) == 3)
    		caid_result = 46.1;
    	else
    		caid_result = 92.3;
    }
    return caid_result;
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_massharm_ingredients(object caster)
{ 
    return ({ "_syndyasmos_component_" });
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
    
    if (caster->query_wiz_level())
    {
        // Wizards get all spells
        return 1;
    }
    
    // Only fire clerics get this spell
    if (GUILD_MANAGER->query_primary_element(caster) != "fire")
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
    
    if (!GUILD_MANAGER->query_current_syndyasmos_partner(caster))
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_SYNDYASMOS)
    {
        return 0;
    }

    // Only full master clerics and higher get this spell
    if (!GUILD_MANAGER->query_is_full_master(player))
    {
        return 0;
    }

    // Only players who have finished the Guru quest get this spell
    if (!player->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
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
    string caster_message, caster_name, watcher_message;
    string partner_name, partner_message;
    object partner_ob;
    
    caster_name = capitalize(caster->query_real_name());
    partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
    partner_ob = find_player(partner_name);
    partner_name = capitalize(partner_name);

    caster_message = "You hold out your hand and focus on gathering the "+
        "power of Lord Pyros.\n"+partner_name+" holds out "+
        partner_ob->query_possessive()+ " and concentrates intensely.\n";
    partner_message = caster_name+" holds out "+caster->query_possessive()+
        " hand and concentrates intensely.\nYou hold out your hand and focus "+
        "on gathering the power of Lord Diabrecho.\n";
    watcher_message = QCTNAME(caster) + " and "+QTNAME(partner_ob)+
        " both hold out their hands and begin to concentrate intensely.\n";
        
    caster->catch_tell(caster_message);
    partner_ob->catch_tell(partner_message);
    tell_room(environment(caster), watcher_message, 
    	({ caster, partner_ob }), caster);

    setuid();
    seteuid(getuid());
    int conduit_penalty = caster->query_prop(CONDUIT_PENALTY);
    
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
		        "The Conduit between the Circle and the Five suffers from "+
		        "your lack of Faith.\n\n\n");
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
    string partner_name, partner_message;
    object partner_ob;    
    int phurt = result[0];
    string hitloc_desc = result[1];
    
    partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
    partner_ob = find_player(partner_name);
    partner_name = capitalize(partner_name);

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "Streaks of fire and ice fly towards you with "+
        	"great speed, but at "
            + "the last moment you are able to move aside and dodge them, "
            + "escaping unscathed.\n";
        watcher_message = "Streaks of fire and ice fly towards " + 
        	QTNAME(target) + " with "
            + "great speed, but at the last moment " + target->query_pronoun()
            + " is able to move aside and dodge them, escaping unscathed.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Streaks of fire and ice strike you on the "
                + hitloc_desc + " and barely hurt you.\n";
            watcher_message = "Streaks of fire and ice strike " + 
            	QTNAME(target)
                + " on the " + hitloc_desc + " and barely hurt "
                + target->query_objective() + ".\n";
            break;
            
        case 1..10:
            target_message = "Streaks of fire and ice impact directly "+
            	"into your " + hitloc_desc
                + ".\n";
            watcher_message = "Streaks of fire and ice impact into " + 
            	QTPNAME(target)
                + " " + hitloc_desc + ".\n";
            break;
            
        case 11..25:
            target_message = "You turn your body to try and dodge streaks "+
            	"of fire "
                + "and ice hurtling towards you, but are unable to keep "+
                "them from "
                + "hurting your " + hitloc_desc + ".\n";
            watcher_message = QCTNAME(target) + " turns " 
                + target->query_possessive() + " body to try and dodge "+
                "the streaks "
                + "of fire and ice hurtling towards " + 
                target->query_objective()
                + ", but " + target->query_pronoun() + 
                " is unable to keep them "
                + "from hurting " + target->query_possessive() + " "
                + hitloc_desc + ".\n";
            break;
            
        case 26..40:
            target_message = "A streak of fire strikes you and breaks upon "
                + "contact into burning sparks, searing you on your "
                + hitloc_desc + " and causing many wounds.\n";
            watcher_message = "A streak of fire strikes " + 
            	QTNAME(target) + " and "
                + "breaks upon contact into burning sparks, searing "
                + target->query_objective() + " on " + 
                target->query_possessive()
                + " " + hitloc_desc + " and causing many wounds.\n";
            break;
            
        case 41..65:
            target_message = "A large streak of fire strikes your " + 
            	hitloc_desc + " and "
                + "flames dig into your skin before exploding inside "+
                "of you, causing "
                + "scorching pain.\n";
            watcher_message = "A large streak of fire strikes " + 
            	QTNAME(target) + " on the "
                + hitloc_desc + " and flames dig into " + 
                target->query_possessive()
                + " skin before exploding inside of " + 
                target->query_objective()
                + ", causing scorching pain.\n";
            break;
     
        case 66..99:
            target_message = "Large streaks of fire and ice strike your "
                + hitloc_desc + " so greatly, that you only momentarily "+
                "feel the pain before the fire burns away your nerves and "+
                "the ice freezes your skin.\n";
            watcher_message = "Large streaks of fire and ice strike "
                + QTNAME(target) + " so greatly, that " + 
                target->query_pronoun() +
                " only briefly feels pain before the fire burns away " + 
                target->query_possessive()
                + " nerves and the ice freezes " + 
                target->query_possessive() + " skin.\n";
            break;
            
        // Death (100% hurt or more)
        default:
            target_message = "A massive streak of ice rips through your " +
                hitloc_desc + " and streaks of fire dig into your body and "+
                "explode from within, causing your blood to boil out of your "+
                "body with excruciating pain.\n";
            watcher_message = "A massive streak of ice rips through " + 
            	QTPNAME(target) +
                " " + hitloc_desc + " and streaks of fire dig into " + 
                target->query_possessive()
                + " body and exploding from within, causing the blood to boil "
                + "out of the body with excruciating pain.\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    partner_ob->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, 
    	({ caster, partner_ob, target }));
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
    string partner_message, partner_name, caster_name;
    object partner_ob;

    string go_plural, go_plural2;
    
    partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
    partner_ob = find_player(partner_name);
    partner_name = capitalize(partner_name);
    caster_name = capitalize(caster->query_real_name());

    if(sizeof(targets) > 1)
    {
	    go_plural = "them";
	    go_plural2 = "their";
    }
    else
    {
        go_plural = targets[0]->query_objective();
        go_plural2 = "its";
    }

        caster_message = "A fireball forms in your hand. A frostbolt "+
        	"forms in "+
            QTPNAME(partner_ob)+" hand. You and "+partner_name+
            " push your hands out "+
            "towards each other causing the fireball and frostbolt to "+
            "fly at one another, "+
            "colliding in a violent explosion. Streaks of fire and ice "+
            "from the explosion fly "+
            "off in the direction of " + COMPOSITE_LIVE(targets) + 
            ", leaving wisps of "+
            "frosty air in "+go_plural2+" wake.\n";
        partner_message = "A frostbolt forms in your hand. A fireball "+
        	"forms in "+
            QTPNAME(caster)+" hand. You and "+caster_name+" push your "+
            "hands out "+
            "towards each other causing the fireball and frostbolt to "+
            "fly at one another, "+
            "colliding in a violent explosion. Streaks of fire and ice "+
            "from the explosion fly "+
            "off in the direction of " + COMPOSITE_LIVE(targets) + 
            ", leaving wisps of "+
            "frosty air in "+go_plural2+" wake.\n";
        target_message = "A large fireball forms in "+QTPNAME(caster)+ 
        	" hand. A frostbolt "+
            "forms in "+QTPNAME(partner_ob)+" hand. "+QCTNAME(caster)+
            " and "+
            QTNAME(partner_ob)+" push their hands out towards each "+
            "other causing the "+
            "fireball and frostbolt to fly at one another, colliding "+
            "in a violent explosion. "+
            "Streaks of fire and ice from the explosion fly right "+
            "towards you, leaving wisps of "+
            "frosty air in its wake!\n";

        watcher_message = "A fireball forms in "+QTPNAME(caster)+ 
        	" hand. A frostbolt of air "+
            "forms in "+QTPNAME(partner_ob)+" hand. "+QCTNAME(caster)+
            " and "+QTNAME(partner_ob)+
            " push their hands out towards each other causing the "+
            "fireball and frostbolt to fly at "+
            "one another, colliding in a violent explosion. Streaks of "+
            "fire and ice from the explosion "+
            "fly right towards " + COMPOSITE_LIVE(targets) + 
            ", leaving wisps of frosty air in "+
            go_plural2+" wake.\n";
    
    caster->catch_msg(caster_message);
    partner_ob->catch_msg(partner_message);
    targets->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, 
    	({ caster, partner_ob }) + targets);    
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

public void *
hook_no_present_targets(object actor, string str)
{
    actor->catch_msg("You must first be in combat before you can call "+
    	"on this prayer!\n");
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
    return "blade, alexandrite shard";
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
