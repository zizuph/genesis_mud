/*
 * /d/Gondor/events/event_wep.c
 *
 * Standard weapon base for events.
 *
 * NOTE! When making changes to this file, you must update
 * the file rather than load it for the event wand to work
 * right!
 *
 * Gwyneth September 27, 2000
 */

inherit "/std/weapon";

#include <stdproperties.h>

#include "../events.h"

public void
create_weapon()
{
    set_name("event_weapon");
    set_adj("event");
    set_short("event weapon");
    set_long("This is a generic weapon for events.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
}

string
query_recover()
{
    return 0;
}
