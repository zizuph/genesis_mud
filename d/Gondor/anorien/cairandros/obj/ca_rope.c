/*
 * /d/Gondor/anorien/cairandros/obj/ca_rope.c
 *
 * A length of rope for a quest
 *
 *   Varian - April 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

public void
create_object() 
{
    set_name("rope");
    add_name( ({"caquest_rope", "length"}) );
    add_adj( ({"strong", "length of"}) );

    set_short("strong length of rope");
    set_pshort("strong lengths of rope");
    set_long("This strong length of rope looks like it is designed " +
        "to fit on the windlass of a ballista.\n");
}