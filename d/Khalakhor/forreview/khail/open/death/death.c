/*
 * death.c
 *
 * Death himself, need I say more?
 * Khail, Nov.15/96
 * Based off original death by:
 * Mrpr 901120
 * Tintin 911031
 * Nick 920211
 */
#pragma strict_types
#include <stdproperties.h>

inherit "/std/monster";

/*
 * Function name: create_monster
 * Description  : Sets the variables to create Death.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_monster()
{
    set_name("death");
    add_name("figure");
    add_name("moot");
    add_name("grim reaper");
    set_race_name("immortal");
    set_adj("shadowlike");
    set_short("shadowlike figure, clad in black");
    set_long("An shadowlike figure, clad all in black. This being " +
        "has gone by many names over the eons, such as the Grim " +
        "Reaper, but he is what he is, Death itself, complete " +
        "with a cowled, black robe, and a long, vicious scythe.\n");
    add_item(({"scythe"}),
        "An extremely sharp scythe, so sharp that gusts of wind " +
        "actually try to turn away from the edge rather than be " +
        "sliced in two by the wicked looking blade. It does strange " +
        "things with light as well, seeming to split it's very " +
        "essence into light and dark.\n");
    add_item(({"robe"}),
        "A black hooded robe with numerous pockets. It doesn't " +
        "seem to fit you very well however, as it looks to have " +
        "been tailored for a very lean customer. Someone who's all " +
        "'skin and bones', perhaps...\n");
    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, "Attacking death? Not likely.\n");
    default_config_npc(200);
}

