#pragma no_shadow
#pragma no_inherit
#pragma strict_types
/*
 * - /d/Avenir/union/obj/sway.c
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

public int darkness;
public int invis_sight;
public int new_quick;

public void
create_object(void)
{
    if (!IS_CLONE)
        return;

    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(SWAY_ID);
    add_name(SWAY_ID_ALL);

    // This short is used in the sway messaging.
    set_short("Sway");
    set_long("Can you really see it?\n");

    set_phase_three_message("You feel dizzy, almost drunken on "+
	    "the rush of power pulsing through you. In your "+
	    "heightened state, everything around you seems to "+
	    "be moving excruciatingly slowly, as if your "+
	    "relationship to time has changed.\n");

    set_phase_four_message("The blood in your veins pounds in a furious "+
	    "crescendo, carrying to your ears the echo of beloved "+
	    "voices. Colors seem to be emerging and brightening as "+
	    "the Sway lends deeper sight.\n");

    set_phase_five_message("Your heart pushes liquid fire through your "+
	    "veins, each beat pounding with passion, the essence of "+
	    "your other selves enhancing every sense.\n");

    set_end_sway_message("Suddenly the energy that uplifted you ebbs "+
	    "away. The world around you becomes unfocused and hazy, "+
	    "and a feeling of great weariness falls upon you.\n");
}

/* These effects take place when the sway begins,
   and the Warrior closes their eyes. */
void apply_init_effects(void) {
    ::apply_init_effects();

    darkness = 0;
    new_quick = 0;
    invis_sight = 0;
}

/*
 * Set quickness to a maximum of 25.
 * Set darkvision to 1.
 */
void apply_phase_one_effects(void) {
    ::apply_phase_one_effects();

    new_quick = skill / 4;
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    me->query_combat_object()->cb_update_speed();

    darkness++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);
}

/*
 * Set quickness to a maximum of 25.
 * Set darkvision to 2.
 */
void apply_phase_two_effects(void) {
    ::apply_phase_two_effects();

    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    new_quick = skill * 5 / 20;
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    me->query_combat_object()->cb_update_speed();

    darkness++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);
}

/*
 * Set quickness to a maximum of 30.
 */
void apply_phase_three_effects(void) {
    ::apply_phase_three_effects();

    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    new_quick = skill * 6 / 20;
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    me->query_combat_object()->cb_update_speed();
}

/*
 * Set quickness to a maximum of 30.
 * Set darkvision to 3.
 */
void apply_phase_four_effects(void) {
    ::apply_phase_four_effects();

    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    new_quick = skill * 6 / 20;
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    me->query_combat_object()->cb_update_speed();

    darkness++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);
}

/*
 * Set darkvision to 4.
 */
void apply_phase_five_effects(void) {
    ::apply_phase_five_effects();
    darkness++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);

    invis_sight++;
    ALTER_PROP(me, LIVE_I_SEE_INVIS, 1);
}

/* Remove quickness and darkvision bonuses */
void apply_end_sway_effects(void) {
    ::apply_end_sway_effects();
    if (darkness) {
        ALTER_PROP(me, LIVE_I_SEE_DARK, -darkness);
    }
    if (invis_sight) {
        ALTER_PROP(me, LIVE_I_SEE_INVIS, -invis_sight);
    }
    if (new_quick) {
        ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
        me->query_combat_object()->cb_update_speed();
    }
}
