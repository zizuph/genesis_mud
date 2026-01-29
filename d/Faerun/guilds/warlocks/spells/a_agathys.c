/*
 * Armor of Agathys - Magical protection during battles
 * By Nerull, June 2017
 * 
 * - Added layman caster postfix balance variables.  Nerull 2019
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "evade";


/*
 * Function:    config_evade_spell
 * Description: Config function for evade spells. Redefine this in your
 *              own evade spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_evade_spell()
{
    set_spell_name("viehra");
    set_spell_desc(" - Armor of Agathys: Protection against melee attacks");

    set_spell_combat_aid(30.0);

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);
    
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_ABJURATION, 50);
    set_spell_task(TASK_DIFFICULT);  
    
    set_spell_target(spell_target_caster);
    
    // Spell effect object
    set_spell_object(WARLOCK_SPELLOB_DIR + "a_agathys_obj");
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
        this_player()->catch_tell("Your shield spell runs at maximum capacity.\n");
        
        total_combat_aid = 30.0;  
             
        return (total_combat_aid / 30.0) * 100.0;
    }
    
    total_combat_aid = 15.0;  
    
    this_player()->catch_tell("Your shield spell runs at reduced capacity.\n");

    return (total_combat_aid / 30.0) * 100.0;
}


/*
 * Function:    query_evade_ingredients
 * Description: This function defines what components are required for
 *              this evade spell.
 */
public string *
query_evade_ingredients(object caster)
{
    return ({  });
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
        if (WARLOCK_MAPPINGS->query_warspell_16(this_player()->query_name()) == 2)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= SHIELD_UNLOCK)
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
        if (WARLOCK_MAPPINGS->query_warspell_16(this_player()->query_name()) == 2)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= SHIELD_UNLOCK)
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
    
    // Relevant limitation checks. Only 1 shieldtype on at any time.
    if (present("_protect_life_death_object_", caster) ||
        present("_protect_earth_water_object_", caster) ||
        present("_protect_air_fire_object_", caster))
    {
        this_player()->catch_tell("You have a shield spell active already.\n");
            
        return 0;
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
    
    if (present("_eldritch_sight_object_", this_player()))
    {
        avail_caid -= 20;
    }
    
    if (present("_sculptor_object_", this_player()))
    {
        avail_caid -= 15;
    }
    
    if (present("_witchstep_object_", this_player()))
    {
        avail_caid -= 5;
    }
   
    if (this_player()->query_war_defensive() == 1)
    {
        if (avail_caid < 30)
        {   
            caster->catch_tell("You have too many active magical spells "
            +"in order to cast this spell.\n");
                
            return 0;
        }
    }
    else if (avail_caid < 15)
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
 * Function:    resolve_evade_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_evade_spell(object caster, mixed * targets, int * resist, int result)
{
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already protected by Viehra!\n");
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
    write("You lack the necessary preparations for the "
    +"Viehra spell.\n");
}