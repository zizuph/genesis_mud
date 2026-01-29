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

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "spell_obj_base";

int gCanWield = 0;
int gWeaponDropped = 0;
int gWeaponBroke = 0;
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

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the disarm spell.\n");
    set_spell_effect_desc("disarm");
    
    // 120 CAID so did 60 seconds total
    // 30 seconds guaranteed plus a random amount
    // of the remaining 30 seconds.
    set_dispel_time((30 + (random(30/2)+1) + (random(30/2)+1)));  
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
    string partner_name;
    object partner;
    
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    
    if (caster)
    {
        partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
        partner = find_player(partner_name);
    }        
    
    object *weapons = target->query_weapon(-1);
    gWeapon = weapons[random(sizeof(weapons))];
    
    if (objectp(target))
    {
        target->catch_tell("You feel a sharp pain in your hands.\n");        
    }
    
    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " has been temporarily "+
            "disarmed!\n");
        partner->catch_msg(QCTNAME(target) + " has been temporarily "+
            "disarmed!\n");
    }
    
    target->command("$unwield " + OB_NAME(gWeapon));
    
    if (caster)
    {
        if (caster->is_elemental_racial_cleric)
        {
            // 15% chance to drop the weapon
            if (random(100) > 84)
            {
                // 15% chance to corrode weapon if it drops
                if (random(100) > 84)
                {            
                    gWeapon->set_dull(gWeapon->query_dull() + random(2) + 1);
                    gWeapon->set_corroded(gWeapon->query_corroded() +
                        random(3) + 2);
                    gWeaponDropped = 1;
                    target->catch_tell("The pain is so intense, you drop "+
                        "your " + gWeapon->short() + "!\n");                        
                }
                
                else
                {            
                    target->command("$drop " + OB_NAME(gWeapon));
                    target->catch_tell("The pain is so intense, you drop "+
                        "your " + gWeapon->short() + "!\n");
                    gWeaponDropped = 1;
                }       
            }
        }
        else
        {
            // 10% chance to drop the weapon
            if (random(100) > 89)
            {
                // 10% chance to corrode weapon if it drops
                if (random(100) > 89)
                {            
                    gWeapon->set_dull(gWeapon->query_dull() + random(2) + 1);
                    gWeapon->set_corroded(gWeapon->query_corroded() + 
                        random(3) + 2);
                    gWeaponDropped = 1;
                    target->catch_tell("The pain is so intense, you drop "+
                        "your " + gWeapon->short() + "!\n");                        
                }
                
                else
                {            
                    target->command("$drop " + OB_NAME(gWeapon));
                    target->catch_tell("The pain is so intense, you drop "+
                        "your " + gWeapon->short() + "!\n");
                    gWeaponDropped = 1;
                }       
            }
        }
    }    
    
    gCanWield = 1;
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    string partner_name;
    object partner;
    
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    
    if (caster)
    {
        partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
        partner = find_player(partner_name);
    }

    if (objectp(target))
    {
        target->catch_tell("The pain in your hands subside.\n");
    }

    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " seems "
            + "to be able to wield weapons again.\n");
        partner->catch_msg(QCTNAME(target) + " seems "
            + "to be able to wield weapons again.\n");
    }
    
    gCanWield = 0;
    
    if (!gWeaponBroke)
    {
        if (gWeaponDropped)
        {
        	if (objectp(target))
            	target->command("$get " + OB_NAME(gWeapon));
        }
        if (objectp(target))
        	target->command("$wield " + OB_NAME(gWeapon));
    }
    gWeaponDropped = 0;
    gWeaponBroke = 0;    
}


int
no_wield()
{
    if (!gCanWield)
        return 0;

    write("No, your hands still hurt too much!\n");
    return 1;
}

int
no_take()
{
    if (!gCanWield)
        return 0;

    write("No, your hands still hurt too much!\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(no_wield, "wield");
    add_action(no_wield, "draw");
    add_action(no_wield, "mdraw");
    add_action(no_take,  "take");
    add_action(no_take,  "get");
    add_action(no_take,  "give");
    add_action(no_take,  "pick");
    add_action(no_take,  "steal");
    add_action(no_take,  "borrow");
}
