/*
 * /d/Gondor/events/event_food.c
 *
 * Standard food base for events.
 *
 * NOTE! When making changes to this file, you must update
 * the file rather than load it for the event wand to work
 * right!
 *
 * Gwyneth September 27, 2000
 */

inherit "/std/food";

#include <stdproperties.h>

#include "../events.h"

public void
create_food()
{
    set_name("event_food");
    set_adj("event");
    set_short("event food");
    set_long("This is a generic food for events.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
}

string
query_recover()
{
    return 0;
}
