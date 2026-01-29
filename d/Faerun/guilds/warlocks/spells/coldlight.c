/*
 * A thematic lightspell for the warlocks.
 *
 * Nerull 2017
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
*/

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "light";

// Prototypes
public void resolve_light_spell(object caster, mixed * targets, int * resist,
int result);


/*
 * Function:    config_light_spell
 * Description: Config function for light spells. Redefine this in your
 *              own light spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_light_spell()
{
    set_spell_name("urfiviel");
    set_spell_desc(" - Coldlight: Illuminate the environment with an aura");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_2);

    set_spell_target(spell_target_caster);

    set_spell_element(SS_ELEMENT_WATER, 10);
    set_spell_form(SS_FORM_CONJURATION, 15);
    
    set_spell_task(TASK_ROUTINE);    
        
    // Set the effect object filename
    set_spell_object(WARLOCK_SPELLOB_DIR + "coldlight_obj");
}


/*
 * Function:    query_light_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_light_ingredients(object caster)
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
    
    return ({ "_coldlight_charge" });
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
    
    if (WARLOCK_MASTER->is_lay_warlock(player->query_name()))
    {
        if (player->query_guild_level_lay() >= COLDLIGHT_UNLOCK)
        {
            return 1;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(player->query_name()))
    {
        if (player->query_guild_level_occ() >= COLDLIGHT_UNLOCK)
        {
            return 1;
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
 * Function:    resolve_light_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_light_spell(object caster, mixed * targets, int * resist, int result)
{
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining Urfiviel!\n");
}


/*
* Function:    hook_renew_spell_object
* Description: Message to give when the spell is recast onto an already
*             existing effect. Usually just extends the duration of the spell
*/
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("Your Urfiviel renews.\n");
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
    write("You need the proper preparations for Urfiviel!\n");
}

