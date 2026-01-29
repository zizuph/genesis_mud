/*
 * Coloured flower
 * Boreaulam, January 2014
 */
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/std/object";

void
create_object()
{
    set_name("flower");
    set_short(query_adj() + " flower");
    set_long("This is a " + query_adj() + " flower.\n");
    add_prop(OBJ_I_WEIGHT, 5 + random(5));
    add_prop(OBJ_I_VOLUME, 5 + random(10));
}

void set_colour(string colour)
{
    set_adj(colour);
    set_short(query_adj() + " flower");
    set_long("This is a " + query_adj() + " flower.\n");
}

