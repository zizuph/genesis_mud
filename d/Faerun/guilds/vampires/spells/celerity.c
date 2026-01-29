/*
 * Celerity: Move more quickly
 * By Nerull, June 2017
 *
 * * - Added layman caster postfix balance variables.  Nerull 2021
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "haste";

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "../guild.h"

/*
* Function:    config_haste_spell
* Description: Config function for haste spells. Redefine this in your        
*              own haste spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_haste_spell()
{
    set_spell_name("celerity");
    
    set_spell_desc(" - Imbues you with supernatural speed");

    set_spell_target(spell_target_caster);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_DIFFICULT);

    set_spell_element(SS_ELEMENT_WATER, 50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);

    set_spell_combat_aid(30.0);

    // Set the effect object filename
    set_spell_object(VAMPIRES_SPELLOB_DIR + "celerity_obj");
}


/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float total_combat_aid = 30.0;
    
    return (total_combat_aid / 30.0) * 100.0;
}


/*
* Function:    query_haste_ingredients
* Description: This function defines what components are required for
*              this haste spell.
*/
public string *
query_haste_ingredients(object caster)
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
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) > 0)
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
    
    if (present("_elusiveness_object", caster))
    {
        caster->catch_tell("You already are under the "
        +"effect of the elusiveness spell!\n");

        return 0;
    }
    
    if (present("_resilience_object", caster))
    {
        caster->catch_tell("You already are under the "
        +"effect of the resilience spell!\n");

        return 0;
    }
    
    if (present("_protect_life_object", caster))
    {
        caster->catch_tell("You already are under the "
        +"effect of the lifeward spell!\n");

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

    // Blood-drain
    int bloodamount = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());     
    bloodamount = bloodamount - CELERITY_COST;   
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
* Function:    resolve_resistance_spell
* Description: Called at the beginning of resolve_spell in order to perform
*              spell specific actions.
* Arguments:   Same as resolve_spell
*/
public void
resolve_resistance_spell(object caster, mixed * targets, int * resist, int
result)
{
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You already have Celerity active!\n");
}


/*
* Function:    hook_renew_spell_object
* Description: Message to give when the spell is recast onto an already
existing
*              effect. Usually just extends the duration of the spell
*/
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You renew the duration of Celerity.\n");
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
    write("You need the proper reagent for Celerity!\n");
}

