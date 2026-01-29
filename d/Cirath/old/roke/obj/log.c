/*
 * log.c
 *
 * Used in wild/sh1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

string
query_recover()
{
    return MASTER;
}

void
create_object()
{
    set_name("log");

    set_adj("wooden");
    set_short("wooden log");
    set_long("You could most likely build a nice fire of this log.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
}
