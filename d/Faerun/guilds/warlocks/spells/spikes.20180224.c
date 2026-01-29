/*
 * Spikes: Reflect physical damage back at a foe
 * Based on code by Petros, September 2009
 */

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/reflect";


/*
 * Function:    config_reflect_spell
 * Description: Config function for reflect spells. Redefine this in your
 *              own reflect spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_reflect_spell()
{
    set_spell_name("ormule");
    set_spell_desc(" - Spikes: Reflect physical damage back at a foe");
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_element(SS_ELEMENT_WATER, 50);
    set_spell_form(SS_FORM_ABJURATION, 50);
    set_spell_task(TASK_HARD);    

    set_spell_target(spell_target_caster);

    set_shadow_filename(WARLOCK_SPELLOB_DIR + "spikes_sh");
  
    set_allow_specials(1);
    set_allow_magic_attacks(0);
    set_excluded_target_hit_locations( ({ }) );
    // 80% of damage reflected
    set_reflect_damage_combat_aid(55);
    set_reflect_damage_type(MAGIC_DT);
    // 60% change of damage reflected
    set_reflect_damage_likelihood(60);
}


/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float total_combat_aid = 25.0;
    
    if (this_player()->query_war_defensive() == 1)
    {
        total_combat_aid += 30.0;  
             
        return (total_combat_aid / 55.0) * 100.0;
    }

    return (total_combat_aid / 55.0) * 100.0;
}


/*
 * Function:    query_reflect_ingredients
 * Description: This function defines what components are required for
 *              this reflect spell.
 */
public string *
query_reflect_ingredients(object caster)
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
    
    // If we are testing spells regardless of rank and selection.
    if (SPELLTESTING == 1)
    {
        return 1;
    }

    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MASTER->query_warspell_16(this_player()->query_name()) == 3)
        {
            if (WARLOCK_MASTER->query_desecration_power(this_player()->query_name())
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
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (caster->query_guild_name_lay() != WARLOCK_NAME)
    {
        write("You are not a member of the "+ GUILDNAME_STRING + ".\n");
        return 0;
    }

    // Relevant limitation checks. Only 1 shieldtype on at any time.
    if (caster->query_prop(MR_SHIELD_ON))
    {
       caster->catch_tell("An active resistance shield spell interferes "
	   +"with your ability to cast this spell.\n");
        
        return 0;
    }
	
	if (caster->query_war_defensive() == 0) 
    {
        if (caster->query_prop(ELDRITCH_SIGHT_ON))
        {
            caster->catch_tell("The effect of Eldritch Sight interferes "
            +"with your ability to cast this spell.\n");
        }
        
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


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining the spikes!\n");
}