/*
 * /d/Gondor/events/event_obj.c
 *
 * Standard object base for events.
 *
 * NOTE! When making changes to this file, you must update
 * the file rather than load it for the event wand to work
 * right!
 *
 * Gwyneth September 27, 2000
 */

inherit "/std/object";

#include <stdproperties.h>

#include "../events.h"

public void
create_object()
{
    set_name("event_object");
    set_adj("event");
    set_short("event object");
    set_long("This is a generic object for events.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
}

string
query_recover()
{
    return 0;
}
