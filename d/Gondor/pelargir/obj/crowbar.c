/*
 * /d/Gondor/pelargir/obj/crowbar.c
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
    set_name("crowbar");
    set_short("iron crowbar");
    set_adj( ({ "iron", "heavy", }) );
    set_long(BSN("This is a heavy iron crowbar of the kind used to "
        + "open wooden crates. The flattened end is split, probably "
        + "so the crowbar can be used to pull nails, too."));
    
    set_default_weapon( 4, 8, W_CLUB, W_BLUDGEON, W_ANYH, 0);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON( 4, 8) + 24 + random(25));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON( 8, W_CLUB) + 2000 + random(1001));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
}
