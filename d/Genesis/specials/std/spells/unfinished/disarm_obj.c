/*
 * Standard disarm spell object.
 *
 * Created by Arman Oct 2017. 
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Genesis/specials/std/spells/defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

// The shadow object placed on the weapon that stops the wielder from re-wielding it
// until the disarm duration is up.
#define DISARM_WEAPON_SHADOW "/d/Genesis/specials/std/spells/unfinished/disarm_weapon_sh"

#define DISARM_SPELL_CANNOT_WIELD   ("_disarm_spell_cannot_wield")
#define RECENTLY_SPELL_DISARMED     ("_recently_spell_disarmed")

#define HIS(x) ((x)->query_possessive())
#define HIM(x) ((x)->query_objective())
#define HE(x)  ((x)->query_pronoun())

#define DEBUG(x)	     find_player("arman")->catch_msg("[Disarm] " + x + "\n")

int duration;
object gWeapon = 0;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_disarm_object_");
    set_short("disarm spell object");    
    set_long("This is the standard disarm spell object. " +
             "It disarms the target.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the disarm spell.\n");
    add_prop(OBJ_M_NO_DROP, 1);
    set_spell_effect_desc("disarm");  
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    // Duration is determined depending on the combat aid assigned in the
    // disarm spell. It is passed to the spell object through the 
    // make_spell_object function in resolve spell.

    duration = query_spell_effect_input();   
    set_dispel_time(duration);
    
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }

    return 1;
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
    
    object *weapons = target->query_weapon(-1);
    gWeapon = weapons[random(sizeof(weapons))];

    object weapon_shadow;
    
    if (objectp(target))
    {
        target->catch_tell("You feel your " +gWeapon->short()+ " get incredibly hot " +
            "and burn your hands! You quickly unwield it.\n"); 
        tell_room(environment(target), QCTPNAME(target) + " " +gWeapon->short()+ 
            " is magically superheated, making " +HIM(target)+ " quickly unwield it!\n", 
            ({ caster, target }), caster);       
    }
    
    if (objectp(caster))
    {
        caster->catch_msg(QCTPNAME(target) + " " +gWeapon->short()+ " is magically "+
            "superheated, making " +HIM(target)+ " quickly unwield it!\n");
    }

    // Duration is determined depending on the combat aid assigned in the
    // disarm spell. It is passed to the spell object through the 
    // make_spell_object function in resolve spell, and is called in the
    // shadow placed on the weapon.
    duration = query_spell_effect_input();

    setuid();
    seteuid(getuid());
    weapon_shadow = clone_object(DISARM_WEAPON_SHADOW);
    weapon_shadow->dispel_disarm_spell_shadow(duration);
    weapon_shadow->shadow_me(gWeapon);
    weapon_shadow->initialize_shadow();

    // At 100% combat aid the disarm lasts for 50 seconds. The cooldown is twice the
    // duration of the disarm at 100% caid, so 100 seconds. This time stamp property
    // is checked in the disarm.c spell in the check_valid_action function.
    target->add_prop(RECENTLY_SPELL_DISARMED, time() + 100); 

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

    if (objectp(caster))
    {
        caster->catch_msg(QCTPNAME(target) +" " +gWeapon->short()+ " no longer is " +
            "magically superheated, and " +HE(target)+ " can wield it again.\n");
    }  

    if (objectp(target))
    {
        target->catch_tell("Your " +gWeapon->short()+ " no longer feels magically " +
            "superheated, and you can wield it again.\n");

        // If no other weapon has been rewielded, rewield if in possession
        if(!sizeof(target->query_weapon(-1)) && present(gWeapon, target))
           target->command("$wield " + OB_NAME(gWeapon));
    } 
}
