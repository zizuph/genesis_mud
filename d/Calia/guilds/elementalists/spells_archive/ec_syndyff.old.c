/*
 * Syndyasmos Fire + Fire combination spell the 
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

inherit "/d/Genesis/specials/std/spells/mass_harm";
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
    set_spell_name("fotiafotias");
    set_spell_desc("Syndyasmos Fire + Fire Combination");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_fail("Your prayer fails.\n");
    set_spell_combat_aid(150.0);
    set_spell_task(TASK_HARD);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    // 2.0 times the standard cast time for a harm spell 
    set_spell_time_factor(2.0); 
  
    set_spell_element(SS_ELEMENT_FIRE, 50);
    set_spell_form(SS_FORM_CONJURATION, 50);

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
    		caid_result = 40.0;
    	else
    		caid_result = 80.0;
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
        "on gathering the power of Lord Pyros.\n";
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
		    caster->catch_tell("\n\nYou have acted outside of your "+
		    	"Vow of Service. "+
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
		    caster->catch_tell("\n\nYou have repeatedly violated your Vow "+
		    	"of Service. "+
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
        target_message = "A streak of fire flies towards you with great "+
        	"speed, but at "
            + "the last moment you are able to move aside and dodge it, "
            + "escaping unscathed.\n";
        watcher_message = "A streak of fire flies towards " + QTNAME(target) +
        	" with "
            + "great speed, but at the last moment " + target->query_pronoun()
            + " is able to move aside and dodge it, escaping unscathed.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A streak of fire strikes you on the "
                + hitloc_desc + " and barely hurts you.\n";
            watcher_message = "A streak of fire strikes " + QTNAME(target)
                + " on the " + hitloc_desc + " and barely hurts "
                + target->query_objective() + ".\n";
            break;
            
        case 1..10:
            target_message = "A streak of fire impacts directly into your " + 
            	hitloc_desc
                + ".\n";
            watcher_message = "A streak of fire impacts into " + QTPNAME(target)
                + " " + hitloc_desc + ".\n";
            break;
            
        case 11..25:
            target_message = "You turn your body to try and dodge the "+
            	"streak of fire "
                + "hurtling towards you, but are unable to keep it from "
                + "burning your " + hitloc_desc + ".\n";
            watcher_message = QCTNAME(target) + " turns " 
                + target->query_possessive() + " body to try and dodge the "+
                "streak "
                + "of fire hurtling towards " + target->query_objective()
                + ", but " + target->query_pronoun() + " is unable to keep it "
                + "from burning " + target->query_possessive() + " "
                + hitloc_desc + ".\n";
            break;
            
        case 26..40:
            target_message = "A streak of fire strikes you and breaks upon "
                + "contact into burning sparks, searing you on your "
                + hitloc_desc + " and causing many wounds.\n";
            watcher_message = "A streak of fire strikes " + QTNAME(target) + 
            	" and "
                + "breaks upon contact into burning sparks, searing "
                + target->query_objective() + " on " + 
                target->query_possessive()
                + " " + hitloc_desc + " and causing many wounds.\n";
            break;
            
        case 41..65:
            target_message = "A large streak of fire strikes your " + 
            	hitloc_desc + " and "
                + "flames dig into your skin before exploding inside of "+
                "you, causing "
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
            target_message = "The large streak of fire striking your "
                + hitloc_desc + " is so great, and the heat from the fire so "
                + "incendiary, that you only momentarily feel the pain "
                + "before it burns away your nerves and boils your blood.\n";
            watcher_message = "The impact of the large streak of fire striking "
                + QTNAME(target) + " is so great, and the heat from the fire "
                + "so incendiary, that " + target->query_pronoun() + " only "
                + "briefly feels pain until it burns away " + 
                target->query_possessive()
                + " nerves and boils " + target->query_possessive() + 
                " blood.\n";
            break;
            
        // Death (100% hurt or more)
        default:
            target_message = "A massive streak of fire explodes into sight "
                + "and pummels you on your " + hitloc_desc + ", flames "+
                "digging into "
                + "your body and exploding from within, causing your blood "
                + "to boil out of your body with excruciating pain.\n";
            watcher_message = "A massive streak of fire explodes into sight "
                + "and pummels " + QTNAME(target) + " on " + 
                target->query_possessive()
                + " " + hitloc_desc + ", flames digging into " + 
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

    string go_plural;
    
    partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
    partner_ob = find_player(partner_name);
    partner_name = capitalize(partner_name);
    caster_name = capitalize(caster->query_real_name());

    if(sizeof(targets) > 1)
      go_plural = "them";
    else
      go_plural = targets[0]->query_objective();

        caster_message = "A fireball forms in your hand. Another fireball "+
        	"forms in "+
            QTPNAME(partner_ob)+" hand. You and "+partner_name+" push "+
            "your hands out "+
            "towards each other causing the fireballs to fly at one "+
            "another, colliding "+
            "in a large explosion. Streaks of fire from the explosion "+
            "fly off in the "+
            "direction of " + COMPOSITE_LIVE(targets) + ".\n";
        partner_message = "A fireball forms in your hand. Another "+
        	"fireball forms in "+
            QTPNAME(caster)+" hand. You and "+caster_name+" push your "+
            "hands out "+
            "towards each other causing the fireballs to fly at one "+
            "another, colliding "+
            "in a large explosion. Streaks of fire from the explosion "+
            "fly off in the "+
            "direction of " + COMPOSITE_LIVE(targets) + ".\n";
        target_message = "A large fireball forms in "+QTPNAME(caster)+ 
        	" hand. Another "+
            "fireball forms in "+QTPNAME(partner_ob)+" hand. "+
            QCTNAME(caster)+" and "+
            QTNAME(partner_ob)+" push their hands out towards each "+
            "other causing the "+
            "fireballs to fly at one another, colliding in a large "+
            "explosion. Streaks "+
            "of fire from the explosion fly right towards you!\n";

        watcher_message = "A fireball forms in "+QTPNAME(caster)+ 
        	" hand. Another fireball "+
            "forms in "+QTPNAME(partner_ob)+" hand. "+QCTNAME(caster)+
            " and "+QTNAME(partner_ob)+
            " push their hands out towards each other causing the "+
            "fireballs to fly at "+
            "one another, colliding in a large explosion. Streaks of "+
            "fire from the explosion "+
            "fly right towards " + COMPOSITE_LIVE(targets) + "!\n";
    
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

/* Had to mask the below function from spell_targetting.c */

public object *
spell_target_present_enemies(object actor, string str)
{
    object *enemies = (object *)actor->query_enemy(-1) &
        all_inventory(environment(actor));

    if (!sizeof(enemies))
    {
        actor->catch_msg("You must first be in combat before you "+
        	"can call on this prayer!\n");
        return ({});
    }

    return enemies;
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
