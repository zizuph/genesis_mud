/*
 * Witchbolt - Beam of crackling energy
 * By Nerull, June 2017
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "harm";

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
    set_spell_name("wachiel");
    set_spell_desc(" - Witchbolt: Beam of crackling energy");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_3);

    set_spell_combat_aid(50.0);
    set_spell_task(TASK_DIFFICULT);

    set_spell_time_factor(1.5);

    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_CONJURATION, 50);
}


/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float total_combat_aid = 0.0;   

    if ((present("_eldritch_sight_object_", this_player())) &&
       (present("_protect_life_death_object_", this_player()) ||
        present("_protect_earth_water_object_", this_player()) ||
        present("_protect_air_fire_object_", this_player()) ||
        present("_agathys_shield_object", this_player()) ||
        present("_barkskin_object_", this_player()) ||        
        present("_spikes_object_", this_player())))
    {
        // Darkvision counts for 20 caid.
        if (this_player()->query_war_defensive() == 1) 
        {
            total_combat_aid = 30.0;

            return (total_combat_aid / 50.0) * 100.0;
        }
        
        total_combat_aid = 35.0;

        return (total_combat_aid / 50.0) * 100.0;
    }
    
    if ((present("_warpreality_object_", this_player())) &&
       (present("_protect_life_death_object_", this_player()) ||
        present("_protect_earth_water_object_", this_player()) ||
        present("_protect_air_fire_object_", this_player()) ||
        present("_agathys_shield_object", this_player()) ||
        present("_barkskin_object_", this_player()) ||        
        present("_spikes_object_", this_player())))
    {
        total_combat_aid = 35.0;

        return (total_combat_aid / 50.0) * 100.0;
    }
    
    if ((present("_sculptor_object_", this_player())) &&
       (present("_protect_life_death_object_", this_player()) ||
        present("_protect_earth_water_object_", this_player()) ||
        present("_protect_air_fire_object_", this_player()) ||
        present("_agathys_shield_object", this_player()) ||
        present("_barkskin_object_", this_player()) ||        
        present("_spikes_object_", this_player())))
    {
        total_combat_aid = 35.0;

        return (total_combat_aid / 50.0) * 100.0;
    }
    
    if (present("_warpreality_object_", this_player()) && 
        present("_sculptor_object_", this_player()))
    {
        // Warp reality is 30 caid in offensive mode. Scultor 
        // is always 15, so 80 - 45 = 35.
        if (this_player()->query_war_defensive() == 0) 
        {
            
            total_combat_aid = 35.0;

            return (total_combat_aid / 50.0) * 100.0;
        }
        
        // In defensive mode, scultor and warp reality equals 30,
        // therefore nuke is 50 caid.
        total_combat_aid = 50.0;

        return (total_combat_aid / 50.0) * 100.0;
    }
    
    if (present("_warpreality_object_", this_player()))
    {
        // Darkvision counts for 20 caid.
        if (this_player()->query_war_defensive() == 0) 
        {
            if (present("_eldritch_sight_object_", this_player()))
            {
                total_combat_aid = 30.0;

                return (total_combat_aid / 50.0) * 100.0;
                
            }  
        }
    }
    
    total_combat_aid = 50.0;

    return (total_combat_aid / 50.0) * 100.0;
}


/*
* Function:    query_harm_ingredients
* Description: This function defines what components are required for
*              this harm spell.
*/
public string *
query_harm_ingredients(object caster)
{
    return ({ });
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
        if (WARLOCK_MAPPINGS->query_warspell_19(this_player()->query_name()) == 1)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= NUKE_UNLOCK)
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
        if (WARLOCK_MAPPINGS->query_warspell_19(this_player()->query_name()) == 1)
        {
            if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
                >= NUKE_UNLOCK)
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

    caster_message = "You gather shadows around you, drawing arcane "+
        "power from them as you prepare to cast Wachiel.\n";
    
    watcher_message = "Flickering shadows gather around "+QTNAME(caster)+
        " as "+targets[0]->query_pronoun()+" seems to concentrate deeply.\n";

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
    string beam = "beam of crackling energy";

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "The " + beam + " misses.\n";
        
        watcher_message = "The " + beam + " misses " + 
            QTNAME(target)+".\n";
    }
    else
    {
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "The " + beam + " does not connect.\n";
                
            watcher_message = "The " + beam + " does not connect " 
            +"with " + QTPNAME(target)+".\n";
            break;

        case 1..4:      
            target_message = "The " + beam + " connects, forming a sustained " 
            +"arc!\nYou are slightly shocked!\n";
                
            watcher_message = "The " + beam + " connects, forming a " 
            +"sustained arc!\n" + QCTNAME(target) + " appears slightly " 
            +"shocked.\n";
            break;

        case 5..14:
            target_message = "The " + beam + " connects, forming a sustained "
            +"arc!\nYou are shocked!\n";
                
            watcher_message = "The " + beam 
            + " connects, forming a sustained arc!\n"
            +QCTNAME(target)+" appears shocked.\n";
            break;

        case 15..59:
            target_message = "The " + beam + " connects, forming a sustained "
            +"arc!\nYou are severly shocked!\n";
                
            watcher_message = "The " + beam 
            + " connects, forming a sustained arc!\n"
            +QCTNAME(target)+" appears severly shocked.\n";
            break;

        default:
            target_message = "The " + beam 
            + " connects, forming a sustained "
            +"arc!\nBlue sparks race across your body as you are "
            +"electrocuted into a convulsing, smoking heap!\n";
                
            watcher_message = "The " + beam 
            + " connects, forming a sustained arc!\n"
            +"Blue sparks race across "+QTNAME(target)+"'s body as "
            +target->query_pronoun()+" is electrocuted into a convulsing, "
            +"smoking heap.\n";
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
    string caster_message, target_message, watcher_message;
    object target;

    target = targets[0];


    caster_message = "You direct an arc of crackling, blue energy at "
    +QTNAME(target)+"!\n";

    target_message = QCTNAME(caster)+" directs a beam of crackling, "
    +"blue energy at you!\n";

    watcher_message = QTNAME(caster)+" directs a beam of crackling, blue "
    +"energy at "+QTNAME(target)+"!\n";

    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);
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


/*
* Function name: hook_no_ingredients_fail
* Description:   Return the message that should be printed when the caster
*                doesn't have the right ingredients
* Returns:       The message to print.
*/
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You lack the necessary preparations to cast Wachiel!\n");
}
