/*
 * Fear spell for the Warlocks of Faerun
 *
 * Shamelessly borrowed from OotS, by Arman
 *
 * Nerull 2018
 *
 * Updated to new turn_target spell template
 * - Arman, 6 Feb 2022
 */

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "unfinished/turn_target";

/*
 * Function:    config_turn_target_spell
 * Description: Config function for turn_target spells. Redefine this in your
 *              own turn_target spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_turn_target_spell()
{
    set_spell_name("urhaese");
    set_spell_desc(" - Spook: Cause humans and elves to flee");
    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_ILLUSION, 40);
    
    set_spell_task(TASK_ROUTINE);
    set_spell_ingredients(query_turn_target_ingredients);

    // Spell effect object
    set_spell_object(SPELL_OBJ_DIR + "turn_target_obj"); 
}

/*
 * Function name : target_valid
 * Description   : Check whether the target can actually be affected by the spell.
 * Arguments     : object target - The target of the spell.
 */
public int 
target_valid(object target)
{
    string race = target->query_race_name();
        
    if (race == "human" || race == "elf" || race == "sea-elf" || race == "drow")
    {
        return 1;
    }

    return 0;    
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
    
    // Testing access
    if (present("_nerullian_object_", this_player()))
    {
        return 1;
    }
    
    // If we are testing spells regardless of rank and selection.
    if (SPELLTESTING == 1)
    {
        return 1;
    }

    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_warspell_17(this_player()->query_name()) == 1)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= FEAR_UNLOCK)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    return 1;
                }
           }
       }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_warspell_17(this_player()->query_name()) == 1)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= FEAR_UNLOCK)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    return 1;
                }
           }
       }
    }
    
    return 0;
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function:    query_turn_target_ingredients
 * Description: This function defines what components are required for
 *              this turn_target spell.
 */
public string *
query_turn_target_ingredients(object caster)
{
    // If we are testing spells, no components
    if (SPELLTESTING_NOCOMPS == 1)
    {
        return ({ });
    }
    
    // Testing access
    if (present("_nerullian_object_", this_player()))
    {
        return ({ });
    }
    
    return ({  "_aversion_charge" });
}

/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing
specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target) + " resisted your spell.\n");
    target->catch_msg("You resisted " + QTPNAME(caster) + " spell.\n");
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

    caster_message = "As you surreptitiously whisper the long "
    +"forgotten words, the sounds reverberates in increasing "
    +"intensity, only to fade as you draw arcane powers from the "
    +"shadows!\n";
    
    watcher_message = "A chorus of eerie whispers permeate the area in "
    +"increasing intensity, only to fade again as "+QCTNAME(caster)
    +" turns inwards.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}

// HOOKS TO BE DEFINED
public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " is already under the "
        +"effect of Urhaese!\n");
    }
}

public void
hook_maintaining_turn_target(object caster, object target)
{
    caster->catch_msg("You are currently maintaining the Urhaese spell!\n");
}

public void
hook_target_not_valid(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg("You can only cast this spell on "
            +"humans and elves.\n");
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
    write("You are not properly prepared for the Urhaese spell!\n");
}


/*
 * Function name:   resolve_turn_target_spell
 * Description:     Called at the beginning of resolve_spell in order to perform
 *                  spell specific actions.
 * Arguments:       Same as resolve_spell
 * Returns:         Nothing
 */
public void
resolve_turn_target_spell(object caster, mixed * targets, int * resist, int result)
{
    caster->catch_msg(COMPOSITE_LIVE(targets) + " suddenly screams and "
    +"jerks away from you, desperately looking for an exit!\n");
    
    targets->catch_msg("You scream and jerks away as you meet " 
    +QTPNAME(caster) +"'s ominous gaze. You feel your heart racing and you "
    +"desperately looks for an exit!\n");
    
    tell_room(environment(caster), COMPOSITE_LIVE(targets) +" suddenly "
    +"screams and jerks away from "+QTPNAME(caster) +", desperately looking "
    +"for an exit!\n",
    ({ caster }) + targets, caster); 

} /* resolve_turn_target_spell */




















