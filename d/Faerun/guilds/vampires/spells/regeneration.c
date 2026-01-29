/*
 * Regeneration - Heal undead
 * By Nerull, 2021
 *
 * Updated combat aid from 50 to 0, to allow it to remain a layman
 * spell option within the layman caid cap of 50. Under the revised
 * magic system, this will mean this heal will have an effective
 * combat aid of 100 (through cast time white damage loss component).
 *
 * Defensive maintained spell casting restrictions removed.
 *
 * - Arman, 6 April 2022
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "heal";

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../guild.h"


/*
* Function:    config_heal_spell
* Description: Config function for heal spells. Redefine this in your
*              own heal spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_heal_spell()
{
    //set_ability_group(LAY_VAMPIRES_GUILD_NAME);
    
    set_spell_name("regeneration");
    set_spell_desc(" - Knit together wounds to the undead flesh");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_DIFFICULT);

    // Caid of zero, but as a null value may create issues provided
    // a minimal value of 0.1.
    set_spell_combat_aid(0.1);
    set_spell_time_factor(1.0);
    
    set_spell_element(SS_ELEMENT_DEATH, 50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);
}


public status query_heal_harmful(object target)
{
    return !target->query_prop(LIVE_I_UNDEAD);
}


/*
* Function:    query_heal_ingredients
* Description: This function defines what components are required for
*              this heal spell.
*/
public string *
query_heal_ingredients(object caster)
{
    return ({  });
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
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= 250)
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
    
    if (caster->query_ethereal() == 1)
    {
        caster->catch_tell("You are in the ethereal realm. This spell "
        +"doesn't work there.\n");
        
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
    
    if (!targets[0]->query_prop(LIVE_I_UNDEAD))
    {
        write("This spell has no effect on the living.\n");
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
    object target = targets[0];
    
    caster_message = "You concentrate on the restorative "
    +"properties of dark energy.\n";
    
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


// HOOKS TO BE DEFINED


/*
* Function:    resolve_heal_spell
* Description: Called at the beginning of resolve_spell in order to perform
*              spell specific actions.
* Arguments:   Same as resolve_spell
*/
public void
resolve_heal_spell(object caster, object *targets, int *resist, int result)
{
}


/*
* Function name: hook_describe_heal_cast
* Description:   Describe casting of the spell. This takes place before the
*                actual healing happens.
*                This can be redefined for custom messages.
* Arguments:     object caster   - the caster
*                object * target - the target(s)
*/
public void
hook_describe_heal_cast(object caster, object *targets)
{
}


/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    object tar = targets[0];
    
    int heal = heal_amounts[0];
    
    string heal_desc;
    
    switch(heal)
    {
       case 0..50:
         heal_desc = " slightly";
         break;
       case 51..150:
         heal_desc = " somewhat";
         break;
       case 151..250:
         heal_desc = "";
         break;
       case 251..450:
         heal_desc = " decently";
         break;
       case 451..9999:
         heal_desc = " greatly";
         break;
       default:
         heal_desc = "";
         break;
    }
    
    if (tar == caster)
    {
        caster->catch_tell("By focusing the power of the blood, your "
        +"wounds knits together"+heal_desc+ "!\n");   
            
        tell_room(environment(caster), "The wounds of "
        +QCTNAME(caster)+" knits together"+heal_desc+ "!\n", tar);
    }
    else
    {  
        caster->catch_tell("You discreetly channel dark energy into "
        +"the body of "
        +tar->query_the_name(caster)+", who suddenly "
        +"looks"+heal_desc+ " healthier!\n");
        
        tar->catch_tell("You feel dark energy is channeled into your "
        +"very being from someone. You feel" +heal_desc+ " healthier!\n");
                       
        tell_room(environment(caster), QCTNAME(tar)+" suddenly "
        +"looks"+heal_desc+ " healthier as wounded tissue knits together "
        +"in a very unnatural way.\n", ({ caster, tar }), caster);
    }
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




