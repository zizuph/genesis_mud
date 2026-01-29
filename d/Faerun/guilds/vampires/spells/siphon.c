/*
 * Siphon - drain spell
 *
 * Updated combat aid from 50 to 0, to allow it to remain a layman
 * spell option within the layman caid cap of 50. Under the revised
 * magic system, this will mean drain will have an effective
 * combat aid of 100 (through cast time white damage loss component).
 *
 * Defensive maintained spell casting restrictions removed.
 *
 * - Arman, 6 April 2022
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "drain";

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../guild.h"

/*
* Function:    config_harm_spell
* Description: Config function for harm spells. Redefine this in your
*              own harm spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_drain_spell()
{
    //set_ability_group(LAY_VAMPIRES_GUILD_NAME);
    
    set_spell_name("siphon");
    set_spell_desc(" - Channel some of the life of the enemy to you");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    // Caid of zero, but as a null value may create issues provided
    // a minimal value of 0.1.
    set_spell_combat_aid(0.1);
    set_drain_percentage(100);
    set_spell_task(TASK_DIFFICULT);

    set_spell_time_factor(2);

    set_spell_element(SS_ELEMENT_DEATH, 50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);
}


/*
* Function:    query_harm_ingredients
* Description: This function defines what components are required for
*              this harm spell.
*/
public string *
query_drain_ingredients(object caster)
{
    return ({ });
}


/*
* Function:    query_spell_can_be_learned
* Description: Place restrictions on whether this spell can be used
*              by the guild member.
*/
public int
query_spell_can_be_learned(object player)
{
    setuid();
    seteuid(getuid());

    if (!objectp(player))
    {
        return 0;
    }

    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= 900)
    {
        return 1;
    }

    return 0;
}



public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    int a = 0;
    
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!present("_vampire_powers_unlock_ob", caster))
    {
        caster->catch_tell("You are too weak! You "
        +"need to rise from a coffin in order to use this gift.\n");
        
        return 0;
    }
    
    int check = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());
    
    if (check < ABILITY_THRESHOLD)
    {
        caster->catch_tell("The thirst is too overwhelming for you to "
        +"concentrate. Aquire more blood!\n");
        
        return 0;
    }
    
    if (caster->query_ethereal() == 1)
    {
        caster->catch_tell("You are in the ethereal realm. This spell "
        +"doesn't work there.\n");
        
        return 0;
    }
    
    if (targets[0]->query_prop(LIVE_I_UNDEAD))
    {
        write("This spell has no effect on the undead.\n");
        return 0;
    }

/*       
    if ((present("_elusiveness_object", caster)) && (present("_amplify_object", caster)))
    {
        caster->catch_tell("You already are under the "
        +"effect of elusiveness and amplify!\n");

        return 0;
    }
    
    if ((present("_resilience_object", caster)) && (present("_amplify_object", caster)))
    {
        caster->catch_tell("You already are under the "
        +"effect of resilience and amplify!\n");

        return 0;
    }
    
    if ((present("_celerity_object", caster)) && (present("_amplify_object", caster)))
    {
        caster->catch_tell("You already are under the "
        +"effect of celerity and amplify spell!\n");

        return 0;
    }
    
    if ((present("_protect_life_object", caster)) && (present("_amplify_object", caster)))
    {
        caster->catch_tell("You already are under the "
        +"effect of lifeward and amplify!\n");

        return 0;
    }
*/    
    
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
    object target = targets[0];
    
    caster_message = "You concentrate on the power of "
    +"the blood.\n";
    
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
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
desc_drain_damage(object caster, object target, mixed *result, int healing)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "Tendrils of darkness spread out in all "
        +"directions, but you are left unscathed.\n";
        
        watcher_message = "Tendrils of darkness spread out in "
        +"all directions, but " +QTNAME(target)+ " is left unscathed.\n";
    }
    else
    {
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "Strings of darkness barely coil around "
            + hitloc_desc + ", leaving you unharmed.\n";
                
            watcher_message = "Strings of darkness barely coil around "
            +QTPNAME(target)+ " " + hitloc_desc + ", leaving "
            +target->query_objective()+" unharmed.\n";
            break;

        case 1..14:
            target_message = "A wave of darkness causes a sharp pain "
            +"as it envelops your " +hitloc_desc+ ".\n";
                
            watcher_message = QCTNAME(target) + " screams in horror as "
            +target->query_possessive()+" "+hitloc_desc+" sears in pain "
            +"under a wave of darkness.\n";
            break;

        case 15..29:
            target_message = "You suffocate in pain as tendrils "
            +"of darkness entwined with your life source burst "
            +"out of your "+hitloc_desc+".\n";
                
            watcher_message = QCTNAME(target)+" winces in pain as "
            +target->query_possessive()+ " "+hitloc_desc+" is "
            +"enveloped in a dark tentacle.\n";
            break;

        case 30..79:
            target_message = "You fall to your knees, feeling "
            +"drained and exhausted.\n";
            
            watcher_message = QCTNAME(target)+" falls to "+target->query_possessive()+" "
            +"knees, as "+target->query_objective()
            +" is left feeling drained and exhausted.\n";
            break;

        default:
            target_message = "Your inner life force is violently sucked out of you "
            +"as the darkness consumes you!\n";
                
             watcher_message = "Sparkling jolts of life are extinguished as the darkness "
            +"envelopes " +QTNAME(target)+", leaving nothing but an empty husk!\n";
            break;
        }
    }

    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
    
    if (healing)
    {
        target->catch_msg("Your life has been siphoned by " + QTNAME(caster)
        + ".\n");
        
        caster->catch_msg("You feel healthier.\n");
        
        caster->tell_watcher(QCTNAME(caster) + " looks healthier.\n",
        ({ target }));
    }
}


/*
* Function name: desc_harm_cast
* Description:   Describe casting of the spell, not including damage messages.
*                This can be redefined for custom messages.
* Arguments:     object caster - the caster
*                object target - the target
*/
public void
desc_drain_cast(object caster, object * targets)
{
    string caster_message, target_message, watcher_message;
    object target;

    target = targets[0];


    caster_message = "Focusing your will on your enemy's demise, "
    +"darkness coalesces around you and shoots out like tendrils "
    +"straight at "+QTNAME(target)+"!\n";

    target_message = "A devilish smile forms on the lips of " +QCTNAME(caster)+ " as "
    +"darkness coalesces around " +caster->query_possessive()+ " body like tendrils "
    +"which shoot straight at you!/n";

    watcher_message = "A devilish smile forms on the lips of " +QCTNAME(caster)+ " as "
    +"darkness coalesces around " +caster->query_possessive()+ " body like tendrils "
    +"which shoot straight at "+QTNAME(target)+"!\n";

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
resolve_drain_spell(object caster, object *targets, int *resist, int result)
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
    write("");
}