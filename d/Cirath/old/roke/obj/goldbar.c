/*
 * goldbar.c
 *
 * Used in obj/treasurechest.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

string
query_recover()
{
    return MASTER;
}

string
mylong()
{
    if (TP->query_skill(SS_APPR_OBJ) > 40)
        return
            "At the first look this appears to be a gold bar, but when you " +
            "examine it closer you realize that it is nothing but painted lead.\n";

    return "This is a small bar of what appears to be perfectly good gold.\n";
}

void
create_object()
{
    set_short("gold bar");
    set_long("@@mylong");

    set_name("bar");
    set_adj("gold");

    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_WEIGHT, 1930);
    add_prop(OBJ_I_VOLUME, 100);
}
