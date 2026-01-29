/*
 * Scry - See people from afar
 * By nerull, June 2017
 * 
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "scry";


/*
* Function:    config_fartell_spell
* Description: Config function for fartell spells. Redefine this in your
*              own fartell spells to override the defaults.
*/
public void
config_scry_spell()
{
    set_spell_name("urlob");
    set_spell_desc(" - Scry: See people from afar");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_task(TASK_HARD);
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_DIVINATION, 40);
}

/*
 * Function:    query_ability_cooldown_time
 * Description: Returns the cooldown time for spells. By default, spells
 *              do not have cooldown times. However, for at will spells,
 *              it has a default of AT_WILL_SPELL_TIME - MINIMUM_SPELL_TIME
 */
public int
query_ability_cooldown_time()
{
    // Layman guild scries require limitations.
    // Recommended minimum limitations include:
    //   * extended cooldown of at least 30 seconds
    //   * limited scry locations (indoors or outdoors only)
    //   * random scry detail (i.e. from room description to domain location)

    int cooldown_time = max(30, (100 - this_player()->query_skill(SS_FORM_DIVINATION)));
    
    return cooldown_time;
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You are still gathering yourself from your last "
        + "casting of " + short() + ".\n");
}

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their spell again.
 */
public void 
hook_special_complete()
{
    write("You feel able to cast " + short() + " again.\n");
}


/*
* Function:    query_scry_ingredients
* Description: This function defines what components are required for
*              this fartell spell.
*/
public string *
query_scry_ingredients(object caster)
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
    
    return ({ "_scry_charge" });
}


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
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
            >= SCRY_UNLOCK)
        {
            if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return 1;
            }
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
            >= SCRY_UNLOCK)
        {
            if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return 1;
            }
        }
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


/*
* Function:    hook_no_scry_message
* Description: When it is not possible to scry, for whatever reason,
*              this message is given. This applies to no-scry properties
*              as well as trying to scry a wizard or someone linkdead.
* Arguments:   caster - person casting the spell
*              target - the person being scried
*/
public void
hook_no_scry_message(object caster, object target)
{
    caster->catch_tell("Your target is magically protected from being "
    +"scried!\n");
}


/*
* Function:    hook_scry_success
* Description: When there is a successful scry, a message is prepended
*              before the room descriptions. This is where you
*              customize that message.
* Arguments:   caster - person casting the spell
*              target - the person being scried
*              brief  - whether the description will be brief or not
*/
public void
hook_scry_success(object caster, object target, int brief)
{

    if (brief)
    {
        caster->catch_tell("You vaguely sense your target's surroundings "
        + "through their vision.\n");
    }
    else
    {
        caster->catch_tell("You see your target's surroundings, "
        + "through their vision.\n");
    }

    tell_room(environment(caster), QCTNAME(caster) + " cackles with glee as " +
    caster->query_possessive() + " eyes are focusing on something "
    +"far away for a short "
    +"moment.\n", ({ caster }), caster);
}


/*
 * Function:    hook_notify_been_scried_success
 * Description: A person being scried is notified whenever they are scried.
 *              This message is the one that indicates to them that
 *              the scry was successful.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_notify_been_scried_success(object caster, object target)
{
    target->catch_tell("For a very brief moment, an alien "
    +"presence enters your mind! Flashes of unspeakable "
    +"horrors torment you before the alien presence leaves you "
    +"alone!\nSearing pain rushes through your head for a "
    +"short moment!\n");
    //target->command("grimace");
}