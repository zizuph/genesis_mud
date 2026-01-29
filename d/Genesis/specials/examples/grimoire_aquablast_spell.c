/*
 * Aquablast - Arman 2017
 *
 * At will damage spell for the tutorial
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "at_will_harm";

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

    set_spell_name("aquablast");
    set_spell_desc("A magical blast of scalding water");
    set_spell_element(SS_ELEMENT_WATER, 0);
    set_spell_form(SS_FORM_CONJURATION, 0);

    set_spell_combat_aid(10.0);
    set_spell_task(TASK_ROUTINE); 

    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_WATER));   
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({ "sterling leaf" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(caster->query_skill(SS_SPELLCRAFT) < 10)
    {
       caster->catch_tell("You need to be trained in spellcraft to at least " +
           "superior student to cast this spell.\n");
       return 0;
     }
  
    return 1;
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
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
    
    return 1;
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

        caster_message = "You begin reciting from the leather-bound grimoire"
            + " powerful words of magic, 'Aquablast!'\n";
        watcher_message = QCTNAME(caster) + " begins reciting from a leather-"
            +"bound grimoire mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

// HOOKS TO BE DEFINED

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You are missing a spell component! You must have a broad silver leaf known " +
          "as 'sterling leaf' to cast this spell.\n");
}

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their at will spell again.
 */
public void 
hook_special_complete()
{
    write("You feel ready to conjure a blast of scalding water again.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You do not feel ready to conjure a blast of scalding water again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are currently conjuring a blast of scalding water!\n");
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
   // DEBUG("Target: " +targets[0]->short()+ ", Resist: " +resist[0]+ ", Result: " +result);
}

public void
blast_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A stream of scalding water hisses past you, "
            + "dissipating harmlessly.\n";
        watcher_message = "A stream of scalding water hisses past " + 
            QTNAME(target) + " and dissipates harmlessly.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A stream of scalding water hits your " + hitloc_desc 
                + ", mildly warming it.\n";
            watcher_message = "A stream of scalding water hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", mildly warming it.\n";
            break;
            
        case 1..10:
            target_message = "A stream of scalding water hits your " + hitloc_desc 
                + " causing a mild stinging sensation.\n";
            watcher_message = "A stream of scalding water hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", causing a mild " +
                "stinging sensation.\n";
            break;
            
        case 11..30:
            target_message = "A stream of scalding water explodes in to you, "
                + "blistering your " + hitloc_desc + " painfully.\n";
            watcher_message = "A stream of scalding water explodes in to " + 
                QTNAME(target) + ", blistering " +target->query_possessive()+
                " " + hitloc_desc + " painfully.\n";

            break;
            
        case 31..60:
            target_message = "A stream of scalding water explodes into you, " +
                " causing painful burns and blackening your " 
                +hitloc_desc+ ".\n";
            watcher_message = "A stream of scalding water explodes into "+ 
                QTNAME(target)+ ", causing painful burns and blackening " +
                target->query_possessive()+ " " +hitloc_desc+ ".\n";
            break;
            
        default:
            target_message = "A stream of scalding water explodes in to you, " +
               " fatally burning away flesh and tissue from your " 
               +hitloc_desc+ " and dissolving your bones!\n";

            watcher_message = "A stream of scalding water explodes in to "
                + QTNAME(target) + ", fatally burning away flesh and " +
                "tissue from " +target->query_possessive()+
                " " +hitloc_desc+ " and dissolving " 
                +target->query_possessive()+ " bones!\n"; 
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
aquablast_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];

    blast_desc_damage(caster, target, phurt, hitloc_desc);
  
}

public void
aquablast_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
        caster_message = "You hurl your open hands towards "+ QTNAME(target) + 
            ".\n";
        target_message = QCTNAME(caster) + " hurls " + caster->query_possessive()
            + " open hands towards you.\n";
        watcher_message = QCTNAME(caster) + " hurls " + caster->query_possessive()
            + " open hands towards " + QTNAME(target) + ".\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object *targets)
{
    object target = targets[0];
    aquablast_desc_cast(caster, target);

}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
        aquablast_desc_damage(caster, target, result);
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
        ingredients_description = "sterling leaf";
    }
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        ingredients_description));
}





