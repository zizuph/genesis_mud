/*
 * Reflecting Shroud: Resist magical spells
 * By Nerull, June 2017
 */

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/resistance";


/*
* Function:    config_shadow_spell
* Description: Config function for shadow spells. Redefine this in your
*              own shadow spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_resistance_spell()
{
    set_spell_name("urwem");
    set_spell_desc(" - Reflecting Shroud: Resist Earth and Water spells");

    set_spell_element(SS_ELEMENT_WATER, 50);
    set_spell_form(SS_FORM_ABJURATION, 50);
    set_spell_task(TASK_HARD);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    
    set_spell_target(spell_target_caster);

    set_spell_object(WARLOCK_SPELLOB_DIR + "a_shroud_obj");
}


/*
* Function:    query_resistance_ingredients
* Description: This function defines what components are required for
*              this resistance spell.
*/
public string *
query_resistance_ingredients(object caster)
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
    
    return ({ "_shroud_charge" });
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
       if (WARLOCK_MAPPINGS->query_warspell_18(this_player()->query_name()) == 3)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= MAGICSHIELD_UNLOCK)
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
       if (WARLOCK_MAPPINGS->query_warspell_18(this_player()->query_name()) == 3)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= MAGICSHIELD_UNLOCK)
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
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    // Relevant limitation checks. Only 1 shieldtype on at any time.
    if (present("_agathys_shield_object", caster) ||
        present("_barkskin_object_", caster) ||        
        present("_spikes_object_", caster))
    {
       caster->catch_tell("An active shield spell interferes "
	   +"with your ability to cast this spell.\n");
        
        return 0;
    }
    
    // 2 resistanceskills, 0.9 multiplier
	// starts at 30 (17 caid since its divided on 2 resistances)
	int resist_value = 17;                // 30   /   12
    
    if (this_player()->query_war_defensive() == 1)
    {
        add_resistance(MAGIC_I_RES_EARTH, resist_value); 
        add_resistance(MAGIC_I_RES_WATER, resist_value); 
			
	    return 1;
    }
    
    // 14 caid
	resist_value -= 8;
    
    add_resistance(MAGIC_I_RES_EARTH, resist_value); 
    add_resistance(MAGIC_I_RES_WATER, resist_value); 

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
* Function:    hook_describe_cast_resistance
* Description: Function that gets called to display the caster casting the
*              spell towards his intended targets.
*/
public void
hook_describe_cast_resistance(object caster, object * targets)
{
    caster->catch_tell("You cast Urwem on yourself!\n");
}