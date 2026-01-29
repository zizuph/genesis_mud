/*
 * Stun Effect Object for the Dragonarmy Autoimpale
 * 
 * This is the stun effect object for the dragonarmy's autoimpale. This
 * autoimpale has two effects: damage and stun. This is better than the
 * autoimpale for Militia, which only has damage.
 *
 * Created by Petros, February 2009
 */
 
#pragma strict_types

#include "defs.h"

inherit "/d/Genesis/specials/std/stun_obj_base";

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
    set_name("_autoimpale_stun_object_");
    add_name( ({"autoimpale_stun_obj" }) );
    set_short("hidden autoimpale stun object");    
    set_long("An autoimpale stun object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    // With a cycle time of 240 seconds at 5% combat aid, that means
    // 12 seconds of stun, with the maximum of 36 seconds for cooldown
    // on the stun. Times will be slightly higher with the 90% chance
    // on the autoimpale tohit.
    set_stun_combat_aid(5);
    set_stun_tohit(90); // has a 90% chance of autoimpale hitting.
    set_stun_chance(100); // once hit, stun should always hit.
    set_stun_cycle_time(240);    
}
