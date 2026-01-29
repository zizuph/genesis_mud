/*
 * Frenzy: Move more quickly
 * By Nerull, June 2017
 *
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
    set_spell_name("frenzy");
    
    set_spell_desc(" - Inner raging fire that makes you move faster");

    set_spell_target(spell_target_caster);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_DIFFICULT);

    set_spell_element(SS_ELEMENT_FIRE, 50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);

    set_spell_combat_aid(30.0);

    // Set the effect object filename
    set_spell_object(BF_SPELLOB_DIR + "haste_obj");
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
    return ({ "_frenzy_charge" });
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
    
	if (player->query_guild_level_lay() >= GIFT_5)
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

    caster_message = "You invoke the power of Kossuth!\n";
    
    watcher_message = QCTNAME(caster)
    +" invokes the power of Kossuth!\n";

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
    write("You already have Frenzy active!\n");
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
    write("You renew the duration of Frenzy.\n");
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
    write("You need the proper reagent for Frenzy!\n");
}

