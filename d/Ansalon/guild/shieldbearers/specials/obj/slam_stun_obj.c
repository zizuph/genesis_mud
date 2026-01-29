/*
 * Stun Effect Object for the Shield Slam
 * 
 * This is the stun effect object for slam that handles stun in 
 * conjunction with the stun shadow. stun objects stack with one another.
 *
 * Created by Petros, September 2008
 * Modified:
 * - Increased caid in accordance to the recode.
 *   Carnak
 */
 
#pragma strict_types

#include "guild.h"

inherit SLAM_STUN_POWER;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes

// Global Variables


/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_slam_stun_object_");
    add_name( ({"slam_stun_obj" }) );
    set_short("hidden slam stun object");    
    set_long("A slam stun object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    set_stun_combat_aid(50);
    set_stun_tohit(75);
    set_stun_chance(100); 
    // Cycle time of 30 seconds == 15 seconds stun, 15 seconds cooldown
    // if the aid is 100%. At 25% combat aid, this equals 5 seconds
    // of stun, and 15 seconds of cooldown.
    set_stun_cycle_time(34);    
}
