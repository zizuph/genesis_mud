/*
 * Based on Eowul's code for graded weapons as are found and
 * designed for Mirkwood.
 * 
 * Varian 2015
 */

#pragma strict_types

#include "/d/Genesis/start/human/wild2/bandit/wild.h"

inherit "/std/weapon";
inherit MIRKWOOD_OBJ_DIR + "effects/stat_bonus";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

int do_stab(string str);

void
create_stat_bonus_weapon() 
{
    set_name(({"avoris"}));
    add_name(({"cutlass", "sword"}));
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

init()
{
    ::init();
    add_action("do_stab","stab");
}

int
do_stab(string str)
{
    notify_fail("Stab what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Gripping the handle of your notched shortsword tightly, you " +
        "quickly lunge forward with a dangerous looking stab.\n");
    SAYBB(" lunges forward with surprising speed, the notched shortsword " +
        "in their hand jabbing out with a dangerous looking stab.");
    return 1;
}