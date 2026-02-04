/*
 * Minstrel's vibrato harm song - Arman 2019
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

inherit "/d/Genesis/specials/std/spells/harm";

#include "minstrel_spell_hooks.h"

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_harm_spell()
{
    set_ability_group(GUILD_NAME);
    set_spell_name("vibrato");
    set_spell_desc("a harmful blast of discordant sound");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(50.0);
    set_spell_task(TASK_HARD);
    set_spell_fail(minstrel_perform_fail);

    // 1.5 times the standard cast time for a harm spell 
    set_spell_time_factor(1.5);    

    set_spell_resist(spell_resist_illusion); 

    // Minstrels use non-traditional spell skills
    set_spell_element(SG_INSTRUMENTAL, 20);
    set_spell_form(SG_VOCAL, 20);
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{ 
    return ({  });
}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used 
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "vocal, instrument";
}

public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }

    // We don't allow the "cast" verb to be used or
    // the songs of power to show in the spells list
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }

    string * song_list = SONGBOOK_MANAGER->query_power_songs(player);

    if (!IN_ARRAY("blast", song_list))
    {
        return 0;
    }

    if (MEMBER(player))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    // Combat aid impacted by damage to the instrument to
    // a maximum reduction of 45% before the instrument breaks.

    float caid_mod = 100.0;
    object instrument = present("minstrel_instrument", this_player());
    int instrument_damage = instrument->query_damage();

    caid_mod = 100.0 - itof(instrument_damage * 5);
    
    return caid_mod;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    object instrument = present("minstrel_instrument", caster);

    if(query_spell_form_skill() == SG_INSTRUMENTAL ||
       query_spell_element() == SG_INSTRUMENTAL)
    {
        // The instrument is broken if it has 10 damage.
        if(instrument->query_damage() > 9)
        {
            caster->catch_tell(instrument->query_damage_desc()+ " You cannot " +
                "perform with it in such a state!\n");
            return 0;
        }
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
    string voice = caster->query_vocal_skill_adverb();

    caster_message = "You " +voice+ " attempt Vibrato, and the air " +
        "stirs with the beauty and power of the music.\n";
    watcher_message = QCTNAME(caster) +" " +voice+ " attempts a Song of " +
        "Power, and the air stirs with the beauty and power of the music.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from harm's hit_me.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message;
    int phurt = result[0];
    string hitloc_desc = result[1];

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "You are unaffected by the blast of sound.\n";
        watcher_message = QCTNAME(target) + " is unaffected by the " +
            "blast of sound.\n";
    }
    else
    {        
        switch (phurt) // percentage hurt
        {
        case 0:
                target_message = "You are unaffected by the blast of sound.\n";
                watcher_message = QCTNAME(target) + " is unaffected by the " +
                    "blast of sound.\n"; 
            break;
            
        case 1..2:
            target_message = "Your ears are left ringing by a blast of sound.\n";
            watcher_message = QCTPNAME(target)+ " ears are left ringing by a blast of " +
                "sound.\n";
            break;
            
        case 3..5:
            target_message = "You are rattled by a blast of sound.\n";
            watcher_message = QCTNAME(target) + " is rattled by a blast of sound.\n";
            break;
            
        case 6..12:
            target_message = "You are hurt by a blast of discordant music.\n";
            watcher_message = "A blast of discordant music hurts " +QTNAME(target) + 
                ".\n";
            break;
            
        case 13..25:
            target_message = "You are terribly shaken by a powerful blast of music.\n";
            watcher_message = QCTNAME(target) + " is terribly shaken by a powerful blast " +
                "of music.\n";
            break;
            
        case 26..40:
            target_message = "A powerful blast of music knocks you back a few steps.\n";
            watcher_message = QCTNAME(target) + " staggers back as " + target->query_possessive() + 
                " is crushed by a wave of music.\n";
            break;
                    
        case 41..65:
            target_message = "You are forced to the ground by the power of the music.\n";
            watcher_message = QCTNAME(target) + " is forced to the ground by the power " +
                "of the music.\n";
            break;
            
        default:
            target_message = "You are thrown to the ground by a tremendous blast of music.\n";
            watcher_message = QTNAME(target) + " is thrown to the ground by a tremendous " +
                "blast of music.\n";
            break;
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object * targets)
{ 
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{

}

