/*
 *  Amplify - strength stat boost
 *
 *
 * - Added layman caster postfix balance variables.  Nerull 2019
 */


#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "statboost";

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"

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
    set_spell_name("amplify");
    set_spell_desc(" - Amplifies the strength of the vampire");
    
    set_spell_element(SS_ELEMENT_WATER,  50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);
    set_spell_task(TASK_DIFFICULT);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    
    set_spell_combat_aid(20.0);
    
    add_stat_boost(SS_STR, 20);
    
    set_spell_target(spell_target_caster);
   
    set_spell_object(VAMPIRES_SPELLOB_DIR + "amplify_obj");
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
    
    max_boosts[SS_STR] = 20;
 
    return max_boosts;
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
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= 1451)
    {
        return 1;
    }

    return 0;
}


public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
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
    
    return 1;
}



/*
 * Function:    query_statboost_ingredients
 * Description: This function defines what components are required for
 *              this stat boost spell.
 */
public string *
query_statboost_ingredients(object caster)
{
    return ({  });
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are under the effect of Amplify already.\n");
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
    
    // Blood-drain
    int bloodamount = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());     
    bloodamount = bloodamount - AMPLIFY_COST;   
    VAMPIRES_MAPPINGS->set_thirst_gauge(caster->query_name(), bloodamount);

    caster_message = "You concentrate on the powers of the blood!\n";
    
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


/*
 * Function:    hook_describe_cast_statboost
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_statboost(object caster, object * targets)
{
}



