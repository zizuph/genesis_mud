/*
 *  Whichstep Spell - Transmute the weight of carried items
 *  By Nerull, June 2017
 *
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 *
 * Default weight factor set is 140, which equates to 5 combat aid.
 *  - Arman, January 2022.
 */

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "featherweight";


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
    set_spell_name("urhuew");
    set_spell_desc(" - Witchstep: Transmute the weight of carried items");
    set_spell_element(SS_ELEMENT_EARTH,  40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_task(TASK_ROUTINE);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_2);
    
    set_spell_target(spell_target_caster);

    set_spell_object(WARLOCK_SPELLOB_DIR + "witchstep_obj");
}


/*
 * Function:    query_featherweight_ingredients
 * Description: This function defines what components are required for
 *              this featherweight spell.
 */
public string *
query_featherweight_ingredients(object caster)
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
    
    return ({ "_witchstep_charge" });
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
    
    if (WARLOCK_MASTER->is_lay_warlock(player->query_name()))
    {
        if (player->query_guild_level_lay() >= WITCHSTEP_UNLOCK)
        {
            return 1;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(player->query_name()))
    {
        if (player->query_guild_level_occ() >= WITCHSTEP_UNLOCK)
        {
            return 1;
        }
    }

    return 0;
}


public int
check_valid_action(object caster, mixed * targets,
string arg, int execute = 0)
{
    int avail_caid = 50;   
    
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (present("_eldritch_sight_object_", this_player()))
    {
        avail_caid -= 20;
    }
    
    if (present("_sculptor_object_", this_player()))
    {
        avail_caid -= 15;
    }
       
    if (this_player()->query_war_defensive() == 1)
    {    
        if (present("_warpreality_object_", this_player()))
        {
            avail_caid -= 15;
        }
    }
    else if (present("_warpreality_object_", this_player()))
    {
        avail_caid -= 30;
    }
    
    if (this_player()->query_war_defensive() == 1)
    {
        if (present("_protect_life_death_object_", this_player()) ||
        present("_protect_earth_water_object_", this_player()) ||
        present("_protect_air_fire_object_", this_player()) ||
        present("_agathys_shield_object", this_player()) ||
        present("_barkskin_object_", this_player()) ||        
        present("_spikes_object_", this_player()))
        {
            avail_caid -= 30;
        }
    }
    else if (present("_protect_life_death_object_", this_player()) ||
    present("_protect_earth_water_object_", this_player()) ||
    present("_protect_air_fire_object_", this_player()) ||
    present("_agathys_shield_object", this_player()) ||
    present("_barkskin_object_", this_player()) ||        
    present("_spikes_object_", this_player()))
    {
        avail_caid -= 15;
    }
    
    // Needs 5+ caid left to cast this spell
    if (avail_caid < 5)
    {   
        caster->catch_tell("You have too many active magical spells "
        +"in order to cast this spell.\n");
            
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
    write("Your load is already as light as a feather!\n");
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
    write("You renew the duration of Urhuew!\n");
}