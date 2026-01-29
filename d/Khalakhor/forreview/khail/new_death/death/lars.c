/*
 * lars.c
 *
 * He's the man! The one who saves player's butts from
 * Death, to be precise.
 * Khail, Nov.15/96
 */

#pragma strict_types
#include <stdproperties.h>

inherit "/std/monster";

/*
 * Function name: create_monster
 * Description  : Sets the variables to create Lars.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_monster()
{
    set_name("lars");
    set_race_name("immortal");
    set_short("Lars the Implementor");
    set_long("This grand, stately human which stands before you " +
        "is none other than Lars himself! You find yourself " +
        "strangely comforted by the presence of the Creator of " +
        "these lands. Then you think about what kind of a " +
        "twisted mind could have come up with a place like this, " +
        "and wonder if you're safer with Death.\n");
    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, "Attacking Lars? Not likely.\n");
    default_config_npc(200);
}
