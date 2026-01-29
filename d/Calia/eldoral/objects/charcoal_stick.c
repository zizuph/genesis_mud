/*
 * charcoal_stick
 * 
 * This item is part of the 'sword in the stone' quest in
 * eldoral, used with parchment to copy some patterns.
 *
 * Khail, Dec 6/96
 */
#pragma strict_types

#include "defs.h"

inherit "/std/object";

public void
create_object()
{
    set_name("stick");
    add_name("charcoal");
    add_name(ELDORAL_CHARCOAL_NAME);
    set_adj("short");
    add_adj("charcoal");
    set_short("short charcoal stick");
    set_long("This is a simple, short charcoal stick. " +
        "it's been sharpened at one end, and looks to " +
        "be an adequate means of writing or drawing " +
        "something.\n");

    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 100);
}
