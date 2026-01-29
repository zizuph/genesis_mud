/*
 * Disarm Object - based on the Standard Blind Object
 *
 * It disarms the target for a limited duration.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Jaacar, February 2017.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/unfinished/disarm_obj";

#define DISARM_WEAPON_SHADOW "/d/Genesis/specials/std/spells/unfinished/disarm_weapon_sh"

#define DISARM_SPELL_CANNOT_WIELD   ("_disarm_spell_cannot_wield")
#define RECENTLY_SPELL_DISARMED     ("_recently_spell_disarmed")

int gCanWield = 0;
int gWeaponDropped = 0;
int gWeaponBroke = 0;

int duration;
object gWeapon = 0;



/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();        
    
    object *weapons = target->query_weapon(-1);
    gWeapon = weapons[random(sizeof(weapons))];

    object weapon_shadow;
    
    if (objectp(target))
    {
        target->catch_tell("You feel a sharp pain in your hands.\n");        
    }
    
    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " has been temporarily "+
            "disarmed!\n");
    }
    
    // Duration is determined depending on the combat aid assigned in the
    // disarm spell. It is passed to the spell object through the 
    // make_spell_object function in resolve spell, and is called in the
    // shadow placed on the weapon.
    duration = query_spell_effect_input();
    
    int num_targs = caster->query_prop(LIVE_I_SYNDYASMOS_TARGETS);
    if (num_targs < 1)
        num_targs = 1;
        
    duration = (duration / num_targs);

    setuid();
    seteuid(getuid());
    weapon_shadow = clone_object(DISARM_WEAPON_SHADOW);
    weapon_shadow->dispel_disarm_spell_shadow(duration);
    weapon_shadow->shadow_me(gWeapon);
    weapon_shadow->initialize_shadow();

    // At 100% combat aid the disarm lasts for 50 seconds. The cooldown is twice the
    // duration of the disarm at 100% caid, so 100 seconds. This time stamp property
    // is checked in the disarm.c spell in the check_valid_action function.
    target->add_prop(RECENTLY_SPELL_DISARMED, time() + (duration * 2)); 

    target->add_prop(DISARM_SPELL_CANNOT_WIELD, 1);   
    target->command("$unwield " + OB_NAME(gWeapon));
    
    // 10% chance to break weapon
    if (random(100) > 89)
    {
        
        if (gWeapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
        {
            gWeapon->set_dull(gWeapon->query_dull() + random(2) + 1);
            gWeapon->set_corroded(gWeapon->query_corroded() + 
                random(3) + 2);
        }
        
        else    
        {
            target->catch_tell("The pain is so intense, you drop your "+
            gWeapon->short()+"!\n");
            gWeapon->remove_broken();
            gWeaponBroke = 1;
            target->command("$drop " + OB_NAME(gWeapon));
            target->catch_tell("When it hits the ground, it breaks!\n");
        }            
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();

    target->remove_prop(DISARM_SPELL_CANNOT_WIELD);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The pain in your hands subside.\n");
    }

    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " seems "
            + "to be able to wield weapons again.\n");
    }        
    
    if (objectp(target))
    {
        // If no other weapon has been rewielded, rewield if in possession
        if(!sizeof(target->query_weapon(-1)) && present(gWeapon, target))
           target->command("$wield " + OB_NAME(gWeapon));
    }    
    
    if (!gWeaponBroke)
    {
        if (gWeaponDropped)
        {
        	if (objectp(target))
            	target->command("$get " + OB_NAME(gWeapon));
        }
        if (objectp(target))
        {
            // If no other weapon has been rewielded, rewield if in possession
            if(!sizeof(target->query_weapon(-1)) && present(gWeapon, target))
                target->command("$wield " + OB_NAME(gWeapon));
        }
    }
    gWeaponDropped = 0;
    gWeaponBroke = 0;
    if (caster->query_prop(LIVE_I_SYNDYASMOS_TARGETS))
        caster->remove_prop(LIVE_I_SYNDYASMOS_TARGETS);    
}
