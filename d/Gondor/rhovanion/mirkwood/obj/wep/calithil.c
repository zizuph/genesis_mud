/*
 * Magical weapon found in the spider nests of Mirkwood
 * Major Item 4
 * 
 * Varian 2016
 */

#pragma strict_types

#include "../../defs.h"

inherit MIRKWOOD_OBJ_DIR + "wep/elven_made";
inherit MIRKWOOD_OBJ_DIR + "effects/stat_bonus";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

#define LONG_DESC "A careful inspection of this elegant blade suggests that it is ancient, yet still deadly. Crafted from the finest steel by what must have been a master smith, this sword is not only a mighty weapon, but an object of wondrous beauty. Delicately etched into the blade you can see some elvish script."

int do_read(string str);

void
create_stat_bonus_weapon() 
{
    set_name(({"calithil"}));
    add_name(({"longsword", "sword"}));
    set_short("elegant steel longsword");
    set_adj(({"elegant", "steel"}));
    set_long("@@long_func@@");
            
    set_hit(46);
    set_pen(40);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);

    setup_stat_bonus(SS_DEX, 120, 170, 2);
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
    add_action("do_read", "read");
}

int
do_read(string str)
{
    notify_fail("Were you trying to read the inscription?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("The Elvish script seems to spell out a single name 'Calithil'.\n");
    return 1;
}