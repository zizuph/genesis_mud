/*
 * /d/Gondor/events/event_drink.c
 *
 * Standard drink base for events.
 *
 * NOTE! When making changes to this file, you must update
 * the file rather than load it for the event wand to work
 * right!
 *
 * Gwyneth September 27, 2000
 */

inherit "/std/drink";

#include <stdproperties.h>

#include "../events.h"

public void
create_drink()
{
    set_name("event_drink");
    set_adj("event");
    set_short("event drink");
    set_long("This is a generic drink for events.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
}

string
query_recover()
{
    return 0;
}
