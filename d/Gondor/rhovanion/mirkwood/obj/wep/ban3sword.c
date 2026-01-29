/*
 *  /d/Gondor/rhovanion/mirkwood/obj/wep/stat_bonus_weapon.c
 *
 *  Base for all stat increasing treasure weapons.
 *  Will increase a stat up to a specific stat average, after that
 *  the bonus will decrease rapidly the bigger the player is.
 *
 *  Bonussus are based on imbue level bonussus.
 *
 *  Usage:
 *  
 *  #include <ss_types.h>
 *
 *  public void
 *  create_stat_bonus_weapon()
 *  {
 *      // Setup your weapon as usual
 *      setup_stat_bonus(SS_STR, 50, 70, 2);
 *  }
 *
 *  setup_stat_bonus takes the following arguments:
 *
 *    stat - Which stat to increase (use SS_ constants)
 *    average - Maximum average stat for full effect
 *    max_average - Stat average at which point the bonus is 
 *                  ineffective
 *    bonus_level - How much bonus to give, should be a number
 *                  between 1 and 3, similar to the power/rarity
 *                  of imbues
 *
 *  It is possible to override hook_received_bonus and hook_lost_bonus to
 *  customize messages.
 *
 *  Eowul, Oktober 3rd 2015
 */

#pragma strict_types

#include "../../defs.h"

inherit "/std/weapon";
inherit MIRKWOOD_OBJ_DIR + "effects/stat_bonus";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

void
create_stat_bonus_weapon() 
{
    set_name(({"sword"}));
    add_name(({"cutlass"}));
    set_short("black steel cutlass");
    set_adj(({"black", "steel"}));
    set_long("This cutlass is made of a steel so dark it looks almost black. " +
        "The sword itself is not only incredibly sharp, it is so well " +
        "balanced that it feels as light as a feather in your hands.\n");
            
    set_hit(33);
    set_pen(33);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);

    setup_stat_bonus(SS_STR, 50, 70, 2);
}

nomask void
create_weapon() 
{
    create_stat_bonus_weapon();
    set_wf(this_object());
}

/*
 * Function:    hook_received_bonus
 * Description: Called to write a message to the wielder indicating the bonus
 *              received. Won't be called if the player is not eligable for the
 *              bonus due to too high stat average
 * Arguments:   target - the player receiving the bonus
 *              percentage - how much of the bonus was applied
 * Returns:     0 when normal message should be written
 *              1 when the wield message is written in this function
 */
public int
hook_received_bonus(object target, int percentage)
{
    return 0;
}

/*
 * Function:    hook_lost_bonus
 * Description: Called when the player got the bonus removed (upon unwielding)
 * Arguments:   target - the player loosing the bonus
 * Returns:     0 when normal message should be written
 *              1 when the unwield message is written in this function
 */
public int
hook_lost_bonus(object target)
{
    return 0;
}

public int
wield(object weapon)
{
    object target = environment(this_object());
    int percentage = apply_bonus(target);
    if (percentage != 0) return hook_received_bonus(target, percentage);
    return 0;
}

public int 
unwield(object weapon)
{
    object target = environment(this_object());
    if (remove_bonus(target)) return hook_lost_bonus(target);
    return 0;
}

