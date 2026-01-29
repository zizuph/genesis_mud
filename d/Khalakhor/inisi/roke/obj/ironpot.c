/*
 * ironpot.c
 *
 * Used in nyreese/cas_b7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include "defs.h"
#include <macros.h>

/* Recoverable since it's part of a quest. */
string
query_recover()
{
    return MASTER;
}

void
create_object()
{
    set_name("pot");
    add_name("ironpot");
    set_adj("iron");
    set_short("iron pot");
    set_long("This is a pot, usable to boil things.\n");
  
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 10000);
}
