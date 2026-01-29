/*
 * Warp Reality: Move more quickly
 * By Nerull, June 2017
 *
 * * - Added layman caster postfix balance variables.  Nerull 2019
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "haste";


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
    set_spell_name("uralane");
    
    set_spell_desc(" - Warp Reality: Slows the time and reality around you");

    set_spell_target(spell_target_caster);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_HARD);
    
    set_spell_can_be_renewed(1);

    set_spell_element(SS_ELEMENT_EARTH, 30);
    set_spell_form(SS_FORM_ENCHANTMENT, 35);

    set_spell_combat_aid(30.0);

    // Set the effect object filename
    set_spell_object(WARLOCK_SPELLOB_DIR + "warp_r_obj");
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
    
    if (this_player()->query_war_defensive() == 1) 
    {
        total_combat_aid -= 15.0;
    }
    
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
    
    return ({ "_warp-reality_charge" });
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
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
            >= WARP_REALITY_UNLOCK)
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
            >= WARP_REALITY_UNLOCK)
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
    int a = 0;
    
    int avail_caid = 50;
    
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (present("_eldritch_sight_object_", this_player()))
    {
        avail_caid =- 20;
    }
    
    
    if (present("_sculptor_object_", this_player()))
    {
        avail_caid =- 15;
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
            avail_caid =- 30;
        }
    }
    else if (present("_protect_life_death_object_", this_player()) ||
    present("_protect_earth_water_object_", this_player()) ||
    present("_protect_air_fire_object_", this_player()) ||
    present("_agathys_shield_object", this_player()) ||
    present("_barkskin_object_", this_player()) ||        
    present("_spikes_object_", this_player()))
    {
        avail_caid =- 15;
    }
    
    if (present("_witchstep_object_", this_player()))
    {
        avail_caid =- 5;
    }
    
    if (this_player()->query_war_defensive() == 1)
    {
        if (avail_caid < 15)
        {   
            caster->catch_tell("You have too many active magical spells "
            +"in order to cast this spell.\n");
                
            return 0;
        }
    }
    else if (avail_caid < 30)
    {   
        caster->catch_tell("You have too many active magical spells "
        +"in order to cast this spell.\n");
            
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
    write("You have already this spell active!\n");
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
    write("You renew the duration of Uralane.\n");
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
    write("You need the proper reagent for Uralane!\n");
}

