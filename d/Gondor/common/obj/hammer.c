/*
 * /d/Gondor/common/obj/hammer.c
 *
 * Olorin, January 1997
 *
 * Copyright (c) 1997 by Christian Markus
 */
#pragma strict_types

inherit "/std/weapon.c";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_weapon()
{
    set_name("hammer");
    set_short("iron hammer");
    set_adj( ({ "iron", "heavy", }) );
    set_long(BSN("This is a heavy iron hammer with a wooden handle of "
        + "the kind used by carpenters and shipwrights for heavy "
        + "work. The iron head is oblong in shape, with a hole in "
        + "the middle for the handle."));
    
    set_default_weapon( 4, 8, W_CLUB, W_BLUDGEON, W_ANYH, 0);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON( 4, 8) + 24 + random(25));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON( 8, W_CLUB) + 1000 + random(501));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
