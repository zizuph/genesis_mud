/* File:          /d/Khalakhor/common/poisons/beathap.c
 * Creator:       Teth
 * Date:          January 22, 1998
 * Modifications:  
 * Purpose:       This is the poison from the beatha herb. 
 * Related Files: /d/Khalakhor/common/herbs/beatha.c
 * Comments:      This is a nasty poison for undeads.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
create_poison_effect()
{
    set_name("_undead_beatha_poison");
    set_interval(45); /* 45 seconds */
    set_time(960); /* 16 minutes */
    set_damage(({ POISON_HP, 250, POISON_STAT, SS_STR,
        POISON_STAT, SS_STR, POISON_STAT, SS_CON,
        POISON_STAT, SS_CON, POISON_STAT, SS_CON,
        POISON_STAT, SS_WIS, POISON_STAT, SS_DIS,
        POISON_MANA, 100, POISON_FATIGUE, 20 }));
    set_strength(75); /* Quite strong, yes. */
    set_poison_type("herb");
    set_silent(1); /* No silly gag messages for undead */
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);    
}


