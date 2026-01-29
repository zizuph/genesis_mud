/*
 *  Augumentation - Transmute the weight of carried items
 *  By Nerull, June 2022
 *
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2022
 *
 * Default weight factor set is 140, which equates to 5 combat aid.
 *  - Arman, January 2022.
 */

inherit "/d/Genesis/specials/new/magic/spells/featherweight";
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"



/*
 * Function:    config_featherweight_spell
 * Description: Config function for featherweight spells. Redefine this
 *              in your
 *              own featherweight spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_featherweight_spell()
{
    set_spell_name("augmentation");
    set_spell_desc(" - Transmute the weight of carried items");
    set_spell_element(SS_ELEMENT_DEATH, 50);
    set_spell_form(SS_FORM_ABJURATION, 50);
    set_spell_task(TASK_DIFFICULT);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    
    set_spell_target(spell_target_caster);

    set_spell_object(VAMPIRES_SPELLOB_DIR + "aug_obj");
}


/*
 * Function:    query_featherweight_ingredients
 * Description: This function defines what components are required for
 *              this featherweight spell.
 */
public string *
query_featherweight_ingredients(object caster)
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
    
    // Blood-drain
    int bloodamount = VAMPIRES_MAPPINGS->query_thirst_gauge(caster->query_real_name());     
    bloodamount = bloodamount - AUGUMENTATION_COST;   
    VAMPIRES_MAPPINGS->set_thirst_gauge(caster->query_name(), bloodamount);

    caster_message = "You concentrate on the power "
    +"of the blood.\n";
    
    watcher_message = QCTNAME(caster)
    +" concentrates on something.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


/*
 * Function:    resolve_featherweight_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_featherweight_spell(object caster, mixed * targets,
int * resist, int result)
{
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("Your load has already reduced weight!\n");
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
    write("You renew the duration of augmentation!\n");
}