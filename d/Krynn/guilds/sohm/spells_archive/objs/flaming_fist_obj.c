/*
 * Reflect Damage Object
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/obj/reflect_obj";

#include "../defs.h"
#include "/d/Krynn/common/defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

// Defines
#define RESIST_LIBRARY          "/d/Genesis/specials/resist"

#define FLAMING_FIST_SUBLOC     "_sohm_flaming_fist_effect_subloc"
#define SOHM_FLAMING_FIST_EFFECT "_sohm_flaming_fist_effect"

int     flicker_alarm, unarmed_bonus, unarmed_skill, power;
int     unarmed_hack = 0;
object  effect_owner;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    ::create_spell_object();
    set_spell_effect_desc("flaming fist");

    set_short("flaming fist spell object");
    // set_reflect_resistance_types( ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_FIRE }) );
    
    power = query_spell_effect_power();
    // Power determines how long the spell lasts
    // int duration = ftoi(log(itof(power)) * 300.0);
    // set_dispel_time(duration);
}

void 
display_flicker_message(object spell_object)
{
    object owner = query_effect_target();
    string caster_message, watcher_message;

    switch (random(3))
    {
        case 0:
        caster_message = "Amber flames swirl up along your forearms.\n";       
        watcher_message = "Amber flames swirl up along " + QTPNAME(owner) + 
            " forearms.\n";
            break;
        
        case 1:
        caster_message = "Amber flames engulfing your fists flicker " +
            "quietly.\n";       
        watcher_message = "Amber flames engulfing " + QTPNAME(owner) + 
            " fists flicker quietly.\n";
            break;
            
        case 2:
        default:
        caster_message = "Flames swirling around your fists suddenly flare " +
            "with a bright amber glow.\n";       
        watcher_message = "Flames swirling around " + QTPNAME(owner) + 
            " fists suddenly flare with a bright amber glow.\n";
            break;
    }

    owner->catch_msg(caster_message);
    tell_room(environment(owner), watcher_message, ({ owner }), owner);
   
    set_alarm(140.0, 0.0, &display_flicker_message(owner));
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();
    effect_owner = target;
    power = query_spell_effect_power();

    if (objectp(target))
    {
        target->catch_tell("Your fists are engulfed in swirling flames.\n");
        tell_room(environment(target), QCTPNAME(target) + " fists are " +
            "engulfed in swirling flames.\n", ({ target }));
        target->add_subloc(FLAMING_FIST_SUBLOC, this_object());
    } 

    unarmed_bonus = min(40, (power / 9));

    // DEBUG("Flaming fist unarmed bonus: " +unarmed_bonus+ ".");

    // Int/wis of 100, spell skills  50 / 75 / 100
    //     spell power:              284 / 302 / 317
    //     unarmed bonus:            31 / 33 / 35

    // Int/wis of 200, spell skills  50 / 75 / 100
    //     spell power:              348 / 364 / 384
    //     unarmed bonus:            38 / 40 / 40

    // Because set_skill_extra doesn't work if skill is zero,
    // putting in a hack until fixed to give the caster one point
    // of skill so it works. Removed in hook_spell_effect_ended

    if(!effect_owner->query_skill(SS_UNARM_COMBAT))
    {
      unarmed_hack = 1;
      effect_owner->set_skill(SS_UNARM_COMBAT, 1);
    }

    effect_owner->set_skill_extra(SS_UNARM_COMBAT, 
         effect_owner->query_skill_extra(SS_UNARM_COMBAT) + unarmed_bonus);

    target->add_prop(SOHM_FLAMING_FIST_EFFECT, 1);

    set_alarm(10.0, 0.0, &display_flicker_message(target));  
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    target->remove_prop(SOHM_FLAMING_FIST_EFFECT);

    effect_owner->set_skill_extra(SS_UNARM_COMBAT, 
           effect_owner->query_skill_extra(SS_UNARM_COMBAT) - unarmed_bonus);

    if(unarmed_hack)
    {
      effect_owner->set_skill(SS_UNARM_COMBAT, 
           effect_owner->query_skill(SS_UNARM_COMBAT) - 1);
    }

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The flames surrounding your fists suddenly " +
            "extinguish.\n");
        tell_room(environment(target), "The flames surrounding " +
            QCTPNAME(target) + " fists suddenly extinguish.\n", 
            ({ target }));
        target->remove_subloc(FLAMING_FIST_SUBLOC);
    }

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense your flaming fists spell begin to " +
            "fade.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the flaming fists spell.\n");
    }    
}


// BELOW THIS LINE IS THE ACTUAL REFLECT DAMAGE SHADOW SPECIFIC CODE

/*
 * Function:    hook_reflect_damage_description
 * Description: Override this function to set your own descriptions on
 *              what happens when the damage gets reflected.
 */
public void
hook_describe_reflect_effect(object player, object attacker, mixed hitme_results)
{
    int phurt = hitme_results[0];
    int dam = hitme_results[3];
    string dam_desc;

    // DEBUG("Flaming fist: phurt " +phurt+ ", damage: " +dam+".");

    switch (phurt) // percentage hurt
    {
        case 0..7:
          dam_desc = " slightly";
        break;
        case 8..20:
          dam_desc = "";
        break;
        case 21..45:
          dam_desc = " badly";
        break;
        default:
          dam_desc = " severely";
        break; 
    }       

    attacker->catch_msg(QCTNAME(player) + " deftly deflects your attack "
        + "with " +HIS(player)+ " flaming fists, "+
        "burning you"+dam_desc+".\n");
    player->catch_msg("You deftly deflect the attack on you by " + 
        QTNAME(attacker)+ " with your flaming fists, burning " +
        HIM(attacker) +dam_desc+".\n");
    tell_room(environment(player), QCTNAME(player) + " deftly "
        + "deflects the attack by " + QTNAME(attacker) + " with " +
        HIS(player)+ " flaming fists, burning " +QTNAME(attacker)+
        dam_desc+" in the process.\n", ({ attacker, player }));

}

/*
 * Function:    query_reflect_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_reflect_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "Your fists are engulfed in a swirling aura of fire.\n";
    else
        return capitalize(HIS(on)) + " fists are engulfed in a swirling " +
                "aura of fire.\n";
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) || 
        subloc != FLAMING_FIST_SUBLOC)
    {
        return on->show_subloc(subloc, on, for_obj); 
    }
    
    return query_reflect_subloc_description(on, for_obj);
}

/* 
 * Function:    hook_is_valid_attack
 * Description: Returns whether the attack qualifies for a reflective
 *              damage. This function should be overridden if someone
 *              wants to use any special conditions.
 */
public int
hook_is_valid_attack(int wcpen, int dt, object attacker, int attack_id, int target_hitloc)
{
    object caster = query_effect_target();

    // If wielding a weapon the reflect damage ability won't work.

    if(!caster->query_weapon(W_RIGHT) && !caster->query_weapon(W_LEFT) && 
       !caster->query_weapon(W_BOTH))
    {
       return 1;
    }

    // DEBUG("Flaming fist: invalid attack function called - weapon wielded.");
    return 0;
}
