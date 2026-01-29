/*
 * Custom Damage Modification Messages for undead ward (thalamos)
 *
 * Created by Arman, April 2022
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

#include "/d/Genesis/specials/local.h"
inherit DAM_MOD_OBJ_BASE;

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    ::create_effect();
    set_name("_thalamos_dam_mod_obj");
    add_name( ({"thalamos dam mod obj" }) );
    set_short("hidden thalamos damage modifer object");    
    set_long("A thalamos damage modifier object. One should not be able to see "+
           "it in their inventory.\n");

    setuid();
    seteuid(getuid());
}

/*
 * Function     : query_dam_mod_valid
 * Description  : Validation function to see whether this damage modifier 
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 *                dt        - int, damage type 
 * Returns      : 0/1 - invalid/valid
 */
public int
query_dam_mod_valid(object player, object attacker, int attack_id, int dt)
{
    // The blessing only works against undead
    if(attacker->query_prop(LIVE_I_UNDEAD) > 0)
        return 1;

    return 0;
}

public void
attack_modified(object player, object attacker, int attack_id)
{
    if (!objectp(attacker) || !objectp(player))
    {
        return;
    }
    
    if (query_dam_mod_absorb())
    {
        string caster_msg, target_msg, watcher_msg;

        switch(random(4))
        {
            case 0:
                caster_msg = "The attack from " + QTNAME(attacker)
                    + " is thwarted by a silvery tendril rushing out"
                    + " from you.\n";
                target_msg = "Your attack is thwarted by a silvery " 
                    + "tendril rushing out from " + QTNAME(player) 
                    + ".\n";
                watcher_msg = QCTPNAME(attacker) + " attack is thwarted " 
                    + "by a silvery tendril rushing out from " 
                    + QTNAME(player) + ".\n";
            break;

            case 1:
                caster_msg = QCTPNAME(attacker) + " attempt to harm "
                    + "you only strikes shadows and silvery mist.\n";
                target_msg = "Your attack on " + QTNAME(player) 
                    + " only strikes shadow and silvery mist.\n";
                watcher_msg = QCTPNAME(attacker) + " on " 
                    + QTNAME(player) + " only strikes shadows and "
                    + "silvery mist.\n";
            break;

            case 2:
                caster_msg = "Shadowy tendrils solidify and ward you from " 
                    + QTPNAME(attacker) + " attack.\n";
                target_msg = "Shadowy tendrils solidify and ward " 
                    + QTNAME(player) + " from your attack.\n";
                watcher_msg = "Shadowy tendrils solidify and ward "
                    + QTNAME(player) + " from " + QCTPNAME(attacker) 
                    + " attack.\n";
            break;

            default:
                caster_msg = "A flicker of silvery light stops the attack from " 
                    + QTNAME(attacker) + ".\n";
                target_msg = "A flicker of silvery light stops your attack on " 
                    + QTNAME(player) + ".\n";
                watcher_msg = "A flicker of silvery light stops "
                    + QCTPNAME(attacker) + " attack on " + QTNAME(player) + ".\n";
            break;
        }

        // absorbs damage
        player->catch_msg(caster_msg);
        attacker->catch_msg(target_msg);
        player->tell_watcher(QCTPNAME(attacker) + " attack is thwarted " 
            + "by a silvery tendril rushing out from " + QTNAME(player)
            + ".\n", ({ player, attacker }));
    }
    else
    {
        ::attack_modified(player, attacker, attack_id);
    }        
}
