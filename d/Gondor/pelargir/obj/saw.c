/*
 * /d/Gondor/pelargir/obj/saw.c
 *
 * Olorin, January 1997
 *
 * Copyright (c) 1997 by Christian Markus
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_weapon()
{
    set_name("saw");
    set_short("rusty saw");
    set_adj( ({ "rusty", }) );
    set_long(BSN("This is a rusty saw of the kind used by carpenters "
        + "and shipwrights to fit wooden boards to the right size. "
        + "It consists of a wide steel blade and a wooden handle."));
    
    set_default_weapon( 2, 5, W_KNIFE, W_SLASH, W_ANYH, 0);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON( 2, 5) + 12 + random(13));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON( 8, W_KNIFE) + 200 + random(101));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
    set_corroded(1);

    add_prop(OBJ_M_NO_SELL, "The shopkeeper in not interested in your rusty saw.\n");
}
