/*
 *      /d/Gondor/common/guild/obj/crate.c
 *
 *      Opus, July 1997
 *
 *      Copyright (c) 1997 by Robert Miller
 *
 *      Note: This was written using /d/Gondor/common/guild/obj/rack.c
 *            as an example.
 */

#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_container()
{
    set_short("wooden crate");
    set_name("crate");
    set_adj("wooden");
    set_long( BSN(
        "This large crate is made of sturdy oak. Nicks and scratches "+ 
        "can be seen from where Rangers have hastily thrown in miscellaneous "+
        "items."));

    add_prop(OBJ_M_NO_GET, "The crate is too heavy. All you manage to do "+
         "is hurt your back.\n");
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

}

