/*
 * Disarm Object - based on the Elementalists disarm spell object
 * by Jaacar, February 2017.
 *
 * For weapons that are imbued, it disarms for a limited duration
 * rather than breaking the weapon.
 *
 * Created by Arman, April 2020.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit "/d/Genesis/specials/std/spells/unfinished/disarm_obj";

#define DISARM_WEAPON_SHADOW "/d/Gondor/guilds/morgulmage/spells/obj/naro_disarm_weapon_sh"

#define DISARM_SPELL_CANNOT_WIELD   ("_disarm_spell_cannot_wield")
#define RECENTLY_SPELL_DISARMED     ("_recently_spell_disarmed")

int gCanWield = 0;
int gWeaponDropped = 0;
int gWeaponBroke = 0;

int duration;
object gWeapon = 0;

public void
set_gweapon(object weapon)
{
    gWeapon = weapon;
}    


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
    
    gWeapon = query_spell_effect_input();       

    if(!gWeapon)
    {    
        object *weapons = target->query_weapon(-1);
        gWeapon = weapons[random(sizeof(weapons))];
    }

    object weapon_shadow;
    
    if (objectp(target))
    {
        target->catch_tell("Your " +gWeapon->short()+ " is " +
            "drawn into the realm of Shadow!\n");  
        tell_room(environment(caster), QCTPNAME(target) + " "
        + gWeapon->short()+ " vanishes into the realm of Shadow!\n", 
        ({ target }));      
    }
    
    // Duration is determined depending on the combat aid assigned in the
    // disarm spell. It is passed to the spell object through the 
    // make_spell_object function in resolve spell, and is called in the
    // shadow placed on the weapon.
    //
    // At 100% combat aid the disarm lasts for 50 seconds.
    //
    // Morgul Mage naro currently provides 55 caid, so duration is 27 seconds.

    duration = 27;

    setuid();
    seteuid(getuid());
    weapon_shadow = clone_object(DISARM_WEAPON_SHADOW);
    weapon_shadow->dispel_disarm_spell_shadow(duration);
    weapon_shadow->shadow_me(gWeapon);
    weapon_shadow->initialize_shadow();

    // At 100% combat aid the disarm lasts for 50 seconds. The cooldown is twice the
    // duration of the disarm at 100% caid, so 100 seconds. This time stamp property
    // is checked in the disarm.c spell in the check_valid_action function.
    //
    // Morgul Mage naro currently provides 55 caid.

    target->add_prop(RECENTLY_SPELL_DISARMED, time() + (duration * 2)); 

    target->add_prop(DISARM_SPELL_CANNOT_WIELD, 1);   
    target->command("$unwield " + OB_NAME(gWeapon));
    
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
        target->catch_tell("Your " +gWeapon->short()+ " returns " +
            "from the realm of Shadow!\n");  
        tell_room(environment(target), QCTPNAME(target) + " "
        + gWeapon->short()+ " returns from the realm of Shadow!\n", 
        ({ target }));
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
}
