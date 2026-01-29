#pragma no_shadow
#pragma no_inherit
#pragma strict_types
/*
 * - /d/Avenir/union/special/sway_obj.c
 *
 * The Sway, balanced form
 * Lilith 210501
 *
 * Revisions:
 *
 */

inherit "/d/Avenir/union/special/sway_obj_base";

#include "special.h"
#include <stdproperties.h>


public void
create_object(void)
{
    if (!IS_CLONE)
        return;

    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(SWAY_ID_AGG);
    add_name(SWAY_ID_ALL);
    
    // Thie short is used in various messages.
    set_short("Aggressive Sway");
    set_long("Can you really see it?\n");

    set_phase_three_message("You feel dizzy, almost drunken on "+
	    "the rush of power pulsing through you. In your "+
	    "heightened state, you feel an aggression " +
            "difficult to quell.\n");

    set_phase_four_message("The blood in your veins pounds in a furious "+
	    "crescendo, carrying to your ears the echo of enraged "+
	    "voices.\n");

    set_phase_five_message("Your heart pushes liquid fire through your "+
	    "veins, each beat pounding with passion, the essence of "+
	    "your other selves enhancing your aggression.\n");

    set_end_sway_message("Suddenly the energy that uplifted you ebbs "+
	    "away. The world around you becomes unfocused and hazy, "+
	    "and a feeling of passiveness falls upon you as " +
            "aggressive adrenaline dissipates from you.\n");
}

public int new_quick;

/* These effects take place when the sway begins,
   and the Warrior closes their eyes. */
void apply_init_effects(void) {
    ::apply_init_effects();

    new_quick = 0;
}

/*
  * Set quickness to a maximum of 25.
 */
void apply_phase_one_effects(void) {
    ::apply_phase_one_effects();

    new_quick = skill / 4;
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    me->query_combat_object()->cb_update_speed();

}

/*
 * Set quickness to a maximum of 30.
 */
void apply_phase_two_effects(void) {
    ::apply_phase_two_effects();

    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    new_quick = skill * 6 / 20;
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    me->query_combat_object()->cb_update_speed();
}

/*
 * Set quickness to a maximum of 35.
 */
void apply_phase_three_effects(void) {
    ::apply_phase_three_effects();

    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    new_quick = skill * 7 / 20;
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    me->query_combat_object()->cb_update_speed();
}

/*
 * Set quickness to a maximum of 45.
 */
void apply_phase_four_effects(void) {
    ::apply_phase_four_effects();

    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    new_quick = skill * 9 / 20;
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    me->query_combat_object()->cb_update_speed();
}

void apply_phase_five_effects(void) {
    ::apply_phase_five_effects();
}

/* Remove quickness bonus */
void apply_end_sway_effects(void) {
    ::apply_end_sway_effects();
    if (new_quick) {
        ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
        me->query_combat_object()->cb_update_speed();
    }
}
