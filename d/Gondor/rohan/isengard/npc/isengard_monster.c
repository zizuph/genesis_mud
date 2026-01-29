/*
 *  /d/Gondor/rohan/isengard/npc/isengard_monster.c
 *
 *  Opus, July 1997
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_isengard_monster()
{
}

public nomask void
create_gondor_monster()
{
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT,    180);
    add_prop(CONT_I_WEIGHT,  75000);
    add_prop(CONT_I_VOLUME,  70000);

    create_isengard_monster();
}
