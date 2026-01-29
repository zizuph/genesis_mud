/*
 * Bark Skin - Transform skin to be hard as bark
 * By Nerull, June 2017
 * Based on Arman's Stoneskin spell. 2017
 */

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/stoneskin";


/*
 * Function:    config_stoneskin_spell
 * Description: Config function for stoneskin spells. Redefine this in your
 *              own stoneskin spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_stoneskin_spell()
{
    set_spell_name("treashi");
    set_spell_desc(" - Barkskin: Transform skin to be hard as bark");
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_combat_aid(30.0);
    set_spell_element(SS_ELEMENT_EARTH, 50);
    set_spell_form(SS_FORM_TRANSMUTATION, 50);
    set_spell_task(TASK_HARD);    
    // Can only cast barkskin on themself
    set_spell_target(spell_target_caster);
    // Spell effect object
    set_spell_object(WARLOCK_SPELLOB_DIR + "barkskin_obj");
}


/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float total_combat_aid = 15.0;
    
    if (this_player()->query_war_defensive() == 1)
    {
        total_combat_aid += 15.0;  
             
        return (total_combat_aid / 30.0) * 100.0;
    }

    return (total_combat_aid / 30.0) * 100.0;
}


/*
 * Function:    query_stoneskin_ingredients
 * Description: This function defines what components are required for
 *              this stoneskin spell.
 */
public string *
query_stoneskin_ingredients(object caster)
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
        if (WARLOCK_MAPPINGS->query_warspell_16(this_player()->query_name()) == 1)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SHIELD_UNLOCK)
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
        if (WARLOCK_MAPPINGS->query_warspell_16(this_player()->query_name()) == 1)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SHIELD_UNLOCK)
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
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    // Relevant limitation checks. Only 1 shieldtype on at any time.
    if (present("_protect_life_death_object_", caster) ||
        present("_protect_earth_water_object_", caster) ||
        present("_protect_air_fire_object_", caster))
    {
       caster->catch_tell("An active resistance shield spell interferes "
	   +"with your ability to cast this spell.\n");
        
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
 * Function:    resolve_stoneskin_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_stoneskin_spell(object caster, mixed * targets, int * resist, int
result)
{
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("Your skin is already as hard as bark. Casting the "
    +"spell again will have no effect!\n");
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
    write("You lack a proper ingredient for the spell Treashi.\n");
}