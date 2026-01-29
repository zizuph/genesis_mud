/*
 * fieldward/objects/northgate_gate.c
 * This object controls the state of the Northgate of Waterdeep.
 * The gate is open during the day, and closed during the night. At night, one
 * may knock on the gate to gain access, note that some logic must be
 * implemented in the rooms connected by this gate.
 * Version 1 of the gate will always let anyone through that knocks, but as
 * alternative routes into the city are implemented, enemies of the city and
 * other unwanted elements will be denied entry.
 *
 *  Created Jun 22 by Brine
 */
#pragma strict_types
#pragma no_clone

#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>

static int open = 1;

void
create_object()
{
    set_short("double portcullis");
    set_long(
        "This is the object controlling the state of the North gate of "
        + "Waterdeep.\n"
    );
}

string
query_short()
{
    return "double portcullis";
}

int
query_open()
{
    return open;
}

void
open_gate()
{
    open = 1;
}

void
close_gate()
{
    open = 0;
}
