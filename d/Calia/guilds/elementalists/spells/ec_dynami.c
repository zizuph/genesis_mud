/*
 * Stat Boost Spell for the Elemental Clerics of Calia
 *
 * Created by Jaacar, January 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <composite.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "statboost";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// Prototypes

/*
 * Function:    is_cleric_child_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_cleric_child_spell()
{
    return 1;
}

/*
 * Function:    config_statboost_spell
 * Description: Config function for stat boost spells. Redefine this in your
 *              own stat boost spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_statboost_spell()
{
    set_spell_name("dynami");
    set_spell_desc("Increase your attributes");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    set_spell_combat_aid(DYNAMI_AID);

    set_spell_stationary(0);

    set_spell_task(TASK_ROUTINE);    
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    // add_stat_boost(SS_CON, 5);
    // add_stat_boost(SS_INT, 5);
    // add_stat_boost(SS_WIS, 5);
    
    set_spell_target(spell_target_caster);

    set_spell_element(SS_ELEMENT_EARTH, 20);
    set_spell_form(SS_FORM_ABJURATION, 25);

    // Set the effect object filename
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "dynami_obj");        
}

/*
 * Function:    query_added_stat_boosts
 * Description: Used when making the spell object. This returns the
 *              list of stat boosts that this spell will provide.
 * Returns:     Mapping of the format: SS_* => combat aid
 */
public mapping
query_added_stat_boosts()
{
    mapping max_boosts = ::query_added_stat_boosts() + ([ ]); // make a copy
    int buff_booster_active = 0;
    object buff;

    if (caster_is_maintaining_aspida_effects(this_player())) 
    {
        if (objectp(buff = present("_aspida_object_", this_player())))
        {
            if(ftoi(buff->query_spell_combat_aid()) > ftoi(BASE_ASPIDA_AID))
            {
                // If a boosted aspida is active, CAID for dynami is reduced

                write("While maintaining a boosted aspida, your " +
                    "dynami prayer is diminished in power.\n");
                buff_booster_active = 1; 
            }
        }
    }

    if (caster_is_maintaining_evimero_effects(this_player())) 
    {
        if (objectp(buff = present("_evimero_object_", this_player())))
        {
            if(ftoi(buff->query_spell_combat_aid()) > ftoi(EVIMERO_AID))
            {
                // If a boosted evimero is active, CAID for dynami is reduced

                write("While maintaining a boosted evimero, your " +
                    "dynami prayer is diminished in power.\n");
                buff_booster_active = 1; 
            }
        }
    }

    if (caster_is_maintaining_kato_effects(this_player())) 
    {
        // If a kato is active, CAID for dynami is reduced
        write("While kato is in effect, your dynami prayer is diminished " +
            "in power.\n");
        buff_booster_active = 1; 
    }
    
    // If they are a child cleric, give them the lowest version of this 
    // spell
    if (GUILD_MANAGER->query_is_child_cleric(this_player()))
    {
        if(buff_booster_active)
        {
            max_boosts[SS_CON] = 1;
            max_boosts[SS_INT] = 2;
            max_boosts[SS_WIS] = 2;
            set_spell_combat_aid(15.0);
        }
        else
        {
            max_boosts[SS_CON] = 5;
            max_boosts[SS_INT] = 5;
            max_boosts[SS_WIS] = 5;
            set_spell_combat_aid(15.0);
        }
    }
    
    // If they are a Master Cleric or higher, give them their branches
    // version of this spell (or the lowest version if they haven't
    // chosen a branch yet) 
    else
    {
        string primary_element = GUILD_MANAGER->query_primary_element(TP);
        
        switch(primary_element)
        {
            case "fire": // 15 CAID
                if (TP->query_prop(CONDUIT_PENALTY) == 3)
                {
                    max_boosts[SS_WIS] = 5;
                }
                else
                {
                    // max_boosts[SS_WIS] = 8;
                    max_boosts[SS_DIS] = 15;
                }
                set_spell_combat_aid(15.0);
                break;
            
            case "air": // 15 CAID
                if (TP->query_prop(CONDUIT_PENALTY) == 3)
                {
                    max_boosts[SS_DEX] = 5;
                    set_spell_combat_aid(5.0);
                }
                else
                {
                    if(buff_booster_active)
                    {
                        max_boosts[SS_DEX] = 5;
                        set_spell_combat_aid(5.0);
                    }
                    else
                    {
                        max_boosts[SS_INT] = 8;
                        max_boosts[SS_DEX] = 7;
                        set_spell_combat_aid(15.0);
                    }
                }

                break;
            
            case "water": // 15 CAID
                if (TP->query_prop(CONDUIT_PENALTY) == 3)
                {
                    max_boosts[SS_WIS] = 5;
                    set_spell_combat_aid(5.0);

                }
                else
                {
                    if(buff_booster_active)
                    {
                        max_boosts[SS_WIS] = 5;
                        set_spell_combat_aid(5.0);
                    }
                    else
                    {
                        max_boosts[SS_INT] = 7;
                        max_boosts[SS_WIS] = 8;
                        set_spell_combat_aid(15.0);
                    }
                }

                break;
               
            case "earth": // 30 CAID or 20 CAID
                if (TP->query_prop(CONDUIT_PENALTY) == 3)
                {
                    max_boosts[SS_CON] = 10;
                    max_boosts[SS_DEX] = 5;
                    set_spell_combat_aid(15.0);
                }
                else
                {
                    if(buff_booster_active)
                    {
                        max_boosts[SS_CON] = 15;
                        max_boosts[SS_DEX] = 5;
                        set_spell_combat_aid(20.0);
                    }
                    else
                    {
                        max_boosts[SS_CON] = 20;
                        max_boosts[SS_DEX] = 10;
                        set_spell_combat_aid(30.0);
                    }
                }

                break;
              
            case "life": // 15 CAID
                if (TP->query_prop(CONDUIT_PENALTY) == 3)
                {
                    max_boosts[SS_WIS] = 5;
                    set_spell_combat_aid(5.0);
                }
                else
                {
                    if(buff_booster_active)
                    {
                         max_boosts[SS_WIS] = 5;
                         set_spell_combat_aid(5.0);
                    }
                    else
                    {
                         max_boosts[SS_INT] = 7;
                         max_boosts[SS_WIS] = 8;
                         set_spell_combat_aid(15.0);
                    }
                }
                break;
            
            default: // 15 CAID
                if (TP->query_prop(CONDUIT_PENALTY) == 3)
                {
                    max_boosts[SS_CON] = 5;
                    max_boosts[SS_INT] = 5;
                    set_spell_combat_aid(10.0);
                }
                else
                {
                    max_boosts[SS_CON] = 5;
                    max_boosts[SS_INT] = 5;
                    max_boosts[SS_WIS] = 5;
                    set_spell_combat_aid(15.0);
                }
                break;
        }
    }

    return max_boosts;
}

/*
 * Function:    query_statboost_ingredients
 * Description: This function defines what components are required for
 *              this statboost spell.
 */
public string *
query_statboost_ingredients(object caster)
{
    string caster = TP->query_real_name();
    string element = GUILD_MANAGER->query_primary_element(caster);
    
    if (GUILD_MANAGER->query_is_child_cleric(caster))
        return ({  });
    else
    {
        switch(element)
        {
            case "fire":
                return ({ "_pyros_component_" });
                break;
        
            case "air":
                return ({ "_aeria_component_" });
                break;
                
            case "water":
                return ({ "_diabrecho_component_"  });
                break;
           
            case "earth":
                return ({ "_gu_component_" });
                break;
                
            case "life":
                return ({ "_psuchae_component_" });
                break;
        }
    }
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

    if (caster_is_maintaining_thalamos_effects(caster)) 
    {
    	write("You cannot use this prayer while maintaining thalamos.\n");
    	return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only invoke the gift of " + query_spell_name() 
            + " upon yourself!\n");
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_DYNAMI)
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
        caster_message = "You press the palms of your hands together and pray "
            + "fervently to Lady Gu for the gift of dynami.\n";
        watcher_message = QCTNAME(caster) + " presses the palms of "
            + caster->query_possessive() + " hands together and prays "
            + "fervently.\n";
        break;
    
    case 1:
    default:
        caster_message = "Clasping your hands together, you concentrate on "
            + "the ancient prayer of Dynami, calling upon Lady Gu to "
            + "provide you with renewed strength.\n";
        watcher_message = QCTNAME(caster) + " clasps "
            + caster->query_possessive()
            + " hands together as " + caster->query_pronoun() + " mutters "
            + "a prayer.\n";
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
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have acted outside of your Vow of "+
		        "Service. This strains your connection with the Circle and "+
		        "the Conduit.\n\n\n");
    		break;
    	case 2:  // halved conduit gain, double conduit cost
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have deliberately violated your "+
		        "Vow of Service. The Conduit between the Circle and the "+
		        "Five suffers from your lack of Faith.\n\n\n");
    		break;
    	case 3:  // halved conduit gain, double conduit cost, halved CAID
    		GUILD_MANAGER->add_practice_level(caster, 1);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 1);
		    GUILD_MANAGER->add_guild_conduit(1);
		    caster->catch_tell("\n\nYou have repeatedly violated your "+
		        "Vow of Service. With such malpractice, your prayers "+
		        "sound weak and hollow.\n\n\n");
    		break;
    	default:
    		GUILD_MANAGER->add_practice_level(caster, 2);
		    GUILD_MANAGER->add_player_conduit_earned(caster, 2);
		    GUILD_MANAGER->add_guild_conduit(2);
    		break;
    }
}

/*
 * Function:    resolve_statboost_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_statboost_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already received the gift of " + query_spell_name() +
        "!\n");
}

/*
 * Function:    hook_describe_cast_statboost
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_statboost(object caster, object * targets)
{
    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
//            caster->catch_tell("You cast dynami upon yourself "
//                + "and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("With the realisation that Lady Gu has "
                + "granted your prayer, you feel tranquility penetrate your "
                + "being. A ghostly, more sturdy image of yourself appears "
                + "next to you and moves into you.\n");
        }
    }
    else
    {
//        caster->catch_tell("You cast dynami upon "
//            + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher("A ghostly image of " + QTNAME(caster) + " appears "
        + "next to " + caster->query_objective() + " before moving into "
        + caster->query_objective() + " and disappearing from sight.\n",
        ({ }) );
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already 
 *              existing effect. Usually just extends the duration of the 
 *              spell
 */
public void
hook_renew_spell_object(object caster, object target)
{
    write("You feel the power of Lady Gu flow into you and renew the effects "
        + "of dynami.\n");
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
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    string caster = TP->query_real_name();
    string element = GUILD_MANAGER->query_primary_element(caster);
    
    if (GUILD_MANAGER->query_is_child_cleric(caster))
        return "none";
    else
    {
        switch(element)
        {
            case "fire":
                return "pyros component (fireweed, ruby shard)";
                break;
            
            case "air":
                return "aeria component (chicory, diamond shard)";
                break;
                
            case "water":
                return "diabrecho component (sargassum, sapphire shard)";
                break;
            
            case "earth":
                return "gu component (cladina, emerald shard)";
                break;
                
            case "life":
                return "psuchae component (drakeroot, alexandrite shard)";
                break;
        }
    }
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
