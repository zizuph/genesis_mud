/*
 * Rejuvenation - Heal yourself
 * By Nerull, 2017
 */

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/heal";


/*
* Function:    config_heal_spell
* Description: Config function for heal spells. Redefine this in your
*              own heal spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_heal_spell()
{
    set_ability_group(GUILD_NAME);
    
    set_spell_name("urhadoele");
    set_spell_desc(" - Rejuvenation: Close wounds");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_ROUTINE);
    set_spell_combat_aid(50.0);
    set_spell_time_factor(2.0);

    set_spell_element(SS_ELEMENT_WATER, 20);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);
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
        
        // haste/stat boost + shield = 45 caid.        -15 penalty caid.
        if (b == 45.0)
        {
            total_combat_aid = 35.0;
    
            return (total_combat_aid / 50.0) * 100.0;
        }
        
        // shield + darkvision = 50 caid.              -20 penalty caid.
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
  
    // haste/stat boost + darkvision = 50 caid.    -20 penalty caid.
    if (a == 50.0)
    {
        total_combat_aid = 30.0;

        return (total_combat_aid / 50.0) * 100.0;
    }
    
    // haste/stat boost + shield = 45 caid.        -15 penalty caid.
    if (a == 45.0)
    {
        total_combat_aid = 35.0;

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
* Function:    query_heal_ingredients
* Description: This function defines what components are required for
*              this heal spell.
*/
public string *
query_heal_ingredients(object caster)
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
    
    return ({ "_rejuvenation_charge" });
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
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
            >= REJUVENATION_UNLOCK)
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
            >= REJUVENATION_UNLOCK)
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
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (targets[0]->query_prop(LIVE_I_UNDEAD))
    {
        write("This spell has no effect on the undead.\n");
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
    object target = targets[0];

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


// HOOKS TO BE DEFINED


/*
* Function:    resolve_heal_spell
* Description: Called at the beginning of resolve_spell in order to perform
*              spell specific actions.
* Arguments:   Same as resolve_spell
*/
public void
resolve_heal_spell(object caster, object *targets, int *resist, int result)
{
}


/*
* Function name: hook_describe_heal_cast
* Description:   Describe casting of the spell. This takes place before the
*                actual healing happens.
*                This can be redefined for custom messages.
* Arguments:     object caster   - the caster
*                object * target - the target(s)
*/
public void
hook_describe_heal_cast(object caster, object *targets)
{
    /*caster->catch_tell("Shadowy tendrils materializes and tends "
    +"to your wounds.\n");
    
    caster->tell_watcher("Shadowy tendrils materializes and tends to the "
    +"wounds of "+QCTNAME(caster) + ".\n",
        ({}));*/
    
}





/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    object tar = targets[0];
    int heal = heal_amounts[0];
    string heal_desc;
    switch(heal)
    {
       case 0..50:
         heal_desc = " slightly";
         break;
       case 51..150:
         heal_desc = " somewhat";
         break;
       case 151..250:
         heal_desc = "";
         break;
       case 251..450:
         heal_desc = " decently";
         break;
       case 451..750:
         heal_desc = " greatly";
         break;
       default:
         heal_desc = "";
         break;
    }
    
    if (tar == caster)
    {
        caster->catch_tell("By focusing the spell on yourself, shadowy "
        +"tendrils materialize and tend "
        +"to your wounds. You feel" +heal_desc+ " healthier.\n");   
            
        tell_room(environment(caster), "Shadowy tendrils materialize "
        +"and tend to the wounds of "+QCTNAME(caster)+", who suddenly "
        +"looks"+heal_desc+ " healthier!\n", tar);
    }
    else
    {  
        caster->catch_tell("Your summoned shadowy tendrils materialize "
        +"and tend to the wounds of "
        +tar->query_the_name(caster)+", who suddenly "
        +"looks"+heal_desc+ " healthier!\n");

        tar->catch_tell("Shadowy tendrils materialize and tend "
        +"to your wounds. You feel" +heal_desc+ " healthier!\n");
                       
        tell_room(environment(caster), "Shadowy tendrils materialize "
        +"and tend to the wounds of "+QTNAME(tar)+", who suddenly "
        +"looks"+heal_desc+ " healthier!\n", ({ caster, tar }), caster);
    }
}


/*
* Function name: hook_describe_harm_result
* Description:   Describe the results of the spell upon its targets. This
*                happens after the healing has happened.
*                This can be redefined for custom messages.
* Arguments:     object caster   - the caster
*                object * target - the target(s)
*                int * harm_amounts - the amounts healed
*/
public void
hook_describe_harm_result(object caster, object *targets, int * harm_amounts)
{
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        switch (harm_amounts[index])
        {
        case 0:
            tell_room(environment(caster), QCTNAME(target)
                + " doesn't look effected by the alien energy.\n", targets);
                
            target->catch_tell("Alien energies enter your body, but "
                + "you are unaffected.\n");
                break;

        case 1..100:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the alien energies.\n", targets);
                
            target->catch_tell("Alien energies enter your body, and "
                + "hurt you slightly.\n");
            break;

        case 101..250:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the alien energies.\n", targets);
                
            target->catch_tell("Alien energies enter your body, and "
                + "hurt you somewhat.\n");
            break;

        case 251..500:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the alien energies.\n", targets);
                
            target->catch_tell("Alien energies enter your body, and "
                + "hurt you moderately.\n");
            break;

        default:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the alien energies.\n", targets);
                
            target->catch_tell("Alien energies enter your body, and "
                + "hurt you greatly.\n");
            break;
        }
    }
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
    write("You lack the necessary preparations to cast Urhadoele!\n");
}




