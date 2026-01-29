/*
 * Eldritch Sight =  See in darkness and invisible creatures
 * By Nerull, June 2017
 */

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/darkvision";


/*
* Function:    config_darkvision_spell
* Description: Config function for darkvision spells. Redefine this in your
*              own darkvision spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_darkvision_spell()
{
    set_spell_name("urhavol");
    set_spell_desc(" - Eldritch Sight: See in darkness and invisible creatures");

    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);

    set_spell_offensive(0);

    set_spell_target(spell_target_caster);

    // Set the effect object filename
    set_spell_object(WARLOCK_SPELLOB_DIR + "e_sight_obj");
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
            >= ELDRITCH_SIGHT_UNLOCK)
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
            >= ELDRITCH_SIGHT_UNLOCK)
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
    
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    
    if (present("_warpreality_object_", caster) || 
        present("_sculptor_object_", caster))
    {
        a = a + 1;
    }
    
    
    if (present("_protect_life_death_object_", caster) ||
        present("_protect_earth_water_object_", caster) ||
        present("_protect_air_fire_object_", caster) ||
        present("_agathys_shield_object", caster) ||
        present("_barkskin_object_", caster) ||        
        present("_spikes_object_", caster))
    {
        a = a + 1;
    }   
    
    if (a == 2)
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


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining the Urhavol spell.\n");
}


/*
* Function:    query_darkvision_ingredients
* Description: This function defines what components are required for
*              this dark vision spell.
*/
public string *
query_darkvision_ingredients(object caster)
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
    
    return ({ "_eldritch-sight_charge" });
}