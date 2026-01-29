/*
 * key.c
 *
 * Used in nyreese/cas_b10.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include "defs.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("key");
    add_name("gratingkey_cadu");
    set_adj("rusty");

    set_short("rusty key");
    set_long("This is a very old rather rusty key.\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
}
