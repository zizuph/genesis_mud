/*
 * Dream - Scare and hurt the enemy with unseen horrors
 *
 * - Added layman caster postfix balance variables.  Nerull 2019
 */

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/harm";
#include "gen_func.c"


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
    
    set_spell_name("ngasha");
    set_spell_desc(" - Dream: Harm your enemy with unseen horrors");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(50.0);
    set_spell_task(TASK_ROUTINE);
    
    set_spell_resist(spell_resist_illusion);

    set_spell_time_factor(1.5);

    set_spell_element(SS_ELEMENT_WATER, 40);
    set_spell_form(SS_FORM_ILLUSION, 40);
}


/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    float total_combat_aid = 0;   
    float base_caid = 50.0;
    float a = 0.0;
    float b = 0.0;
    
    // Defensive mode
    if (this_player()->query_war_defensive() == 1) 
    {  
        // 15 caid
        if (present("_warpreality_object_", this_player()) || 
            present("_sculptor_object_", this_player()))
        {
            b = b + 15.0;
        }
        
        // 20 caid
        if (present("_eldritch_sight_object_", this_player()))
        {
            b = b + 20.0;
        }
     
        // 30 caid
        if (present("_protect_life_death_object_", this_player()) ||
            present("_protect_earth_water_object_", this_player()) ||
            present("_protect_air_fire_object_", this_player()) ||
            present("_agathys_shield_object", this_player()) ||
            present("_barkskin_object_", this_player()) ||        
            present("_spikes_object_", this_player()))
        {
            b = b + 30.0;
        }
        
        // haste/stat boost + darkvision = 35 caid.     0 penalty caid.
        if (b == 35.0)
        {
            total_combat_aid = 50.0;
    
            return (total_combat_aid / 50.0) * 100.0;
        }
        
        // haste/stat boost + shield = 45 caid.        -5 penalty caid.
        if (b == 45.0)
        {
            total_combat_aid = 45.0;
    
            return (total_combat_aid / 50.0) * 100.0;
        }
        
        // shield + darkvision = 50 caid.              -10 penalty caid.
        if (b == 50.0)
        {
            total_combat_aid = 30.0;
    
            return (total_combat_aid / 50.0) * 100.0;
        }
    }
    
    // Offensive mode
    // 30 caid
    else    
    if (present("_warpreality_object_", this_player()) || 
        present("_sculptor_object_", this_player()))
    {
        a = a + 30;
    }
    
    // 20 caid
    if (present("_eldritch_sight_object_", this_player()))
    {
        a = a + 20;
    }
 
    //  15 caid
    if (present("_protect_life_death_object_", this_player()) ||
        present("_protect_earth_water_object_", this_player()) ||
        present("_protect_air_fire_object_", this_player()) ||
        present("_agathys_shield_object", this_player()) ||
        present("_barkskin_object_", this_player()) ||        
        present("_spikes_object_", this_player()))
    {
        a = a + 15;
    }
  
    // haste/stat boost + darkvision = 50 caid.    -10 penalty caid.
    if (a == 50.0)
    {
        total_combat_aid = 30.0;

        return (total_combat_aid / 50.0) * 100.0;
    }
    
    // haste/stat boost + shield = 45 caid.        -5 penalty caid.
    if (a == 45.0)
    {
        total_combat_aid = 45.0;

        return (total_combat_aid / 50.0) * 100.0;
    }
    
    // shield + darkvision = 35 caid.               0 penalty caid.
    if (a == 35.0)
    {
        total_combat_aid = 50.0;

        return (total_combat_aid / 50.0) * 100.0;
    }
 
    total_combat_aid = base_caid;
    
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
        if (WARLOCK_MAPPINGS->query_warspell_19(this_player()->query_name()) == 2)
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
        if (WARLOCK_MAPPINGS->query_warspell_19(this_player()->query_name()) == 2)
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

    caster_message = "You close your eyes and concentrating on images "
    +"of unspeakable horrors from beyond time and space!\n";
    
    watcher_message = QCTNAME(caster)+" turns inwards with closed eyes, "
    +"grimacing in pain and dreadful horror!\n";

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
        target_message = "You feel a dreadful alien presence emerging near "
        +"you, but it fades away almost as quickly as it came.\n";
        
        watcher_message = QCTNAME(target) + "'s eyes darts around in a sense "
        +"of dread, looking for something nearby.\n";
    }
    else
    {
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "You feel a dreadful alien presence emerging "
            +"near you and trying to to enter your mind, but it fails "
            +"and fades away.\n";
        
            watcher_message = QCTNAME(target) + "'s eyes darts around in "
            +"a sense of dread, but shrugs it off.\n";
            break;

        case 1..9:
            target_message = "A dreadful alien presence enters your "
            +"mind!\nAn image of an unspeakable horror closing in on "
            +"your impending doom flashes through your mind, followed "
            +"by a series of shocking jolts of pain!\n";
                
            watcher_message = QCTNAME(target)+ " suddenly gasps as "
            +target->query_possessive()+" eyes closes and the face "
            +"grimaces slightly, as if being in pain!\n";
            break;

        case 10..40:
            target_message = "A dreadful alien presence enters your "
            +"mind!\nAn image of several large alien tentacled "
            +"entities ensnaring you flashes through your mind, followed "
            +"by a series of sharp jolts of pain!\n";
                
            watcher_message = QCTNAME(target)+ " suddenly screams as "
            +target->query_possessive()+" eyes closes and the face "
            +"grimaces, as if being in pain!\n";
            break;

        case 41..85:
            target_message = "A dreadful alien presence enters your "
            +"mind!\nBefore your very eyes, you see huge and uniform "
            +"alien entities with thousands of fanged mouths and "
            +"tentacles are in the process of devouring you!\nThe pain "
            +"of being devoured alive is unbearable!\n";
                
            watcher_message = QCTNAME(target)+ " suddenly screams out "
            +"loud as "+target->query_possessive()+" eyes closes and the face "
            +"grimaces violently, as if being in unbearable pain!\n";
            break;

        default:
            target_message = "A dreadful alien presence enters your "
            +"mind!\nSuddenly, you catch a glimpse of the outside the "
            +"ordered universe and the center of all infinity - an "
            +"amorphous blight of nethermost confusion which "
            +"blasphemes and bubbles, accompanied with the "
            +"sounds of muffled, maddening beating of vile drums "
            +"and thin monotonous whine of accursed flutes!\nThe "
            +"pain that races through your mind is beyond what "
            +"you can bear!";
                
            watcher_message = QCTNAME(target)+ " suddenly gasps as "
            +target->query_possessive()+" eyes close while the mouth "
            +"opens widely as if trying to scream, but no words or "
            +"sounds can be heard!\n";
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


    caster_message = "You project the images of unspeakable horrors"
    +" at "+QTNAME(target)+"!\n";

    target_message = QCTNAME(caster)+" suddenly faces you and opens "
    +caster->query_possessive()+ " eyes!\n";

    watcher_message = QCTNAME(caster)+" suddenly faces "
    +QTNAME(target)+" and opens "+caster->query_possessive()+ " eyes!\n";

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
    write("You lack the necessary preparations to cast Ngasha!\n");
}