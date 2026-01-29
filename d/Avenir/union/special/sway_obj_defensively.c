#pragma no_shadow
#pragma no_inherit
#pragma strict_types
/*
 * - /d/Avenir/union/special/sway_obj.c
 *
 * The Sway, defensive form
 * Lilith 210501
 *
 * Revisions:
 *
 */

inherit "/d/Avenir/union/special/sway_obj_base";

#include "special.h"
#include <stdproperties.h>

object evade_object;

public void
create_object(void)
{
    if (!IS_CLONE)
        return;

    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(SWAY_ID_DEF);
    add_name(SWAY_ID_ALL);

    // This short is used in sway messaging.
    set_short("Defensive Sway");

    set_long("Can you really see it?\n");

    set_phase_three_message("You feel the flow of cautious "+
	    "joy pulsing through you. In this heightened state "+
	    "of connection with Jazur, your enemies will "+
		"surely struggle to follow your every move.\n");

    set_phase_four_message("The blood in your veins pounds in a joyous "+
            "crescendo, carrying to your ears the echo of cautious "+
            "voices.\n");

    set_phase_five_message("Your heart pushes liquid fire through your "+
            "veins, each beat pounding with passion, the essence of "+
            "your other selves enhancing every sense until the very "+
            "ground seems to be vibrating with life.\n");

    set_end_sway_message("Suddenly the energy that uplifted you ebbs "+
	    "away. The world around you becomes unfocused and hazy, "+
	    "and the feeling of anticipation vanishes as keen " +
            "clarity slips away.\n");
}

/* These effects take place when the sway begins,
   and the Warrior closes their eyes. */
void apply_init_effects(void) {
    ::apply_init_effects();

}

/*
  * Create the evade object.  The weight of
  * its boosts for each phase is in the effect
  * code itself.
 */
void apply_phase_one_effects(void) {
    ::apply_phase_one_effects();

    evade_object = clone_object(SWAY_EVADE_OBJ);
    evade_object->set_effect_caster(me);
    evade_object->set_effect_target(me);
    evade_object->move(me, 1);
    evade_object->start();
}

/* Remove the evade object. */
void apply_end_sway_effects(void) {
    ::apply_end_sway_effects();
    if (evade_object) {
        evade_object->remove_object();
    }
}
