/*
 * Revisions:
 *   Lucius, Aug 2016: Made always recoverable.
 *
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>

public void
create_object(void)
{
    set_name("needle");
    set_long("It is a simple needle usually used for sewing.\n");

    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);

    set_keep(1);
    set_may_recover();
}

public string
query_recover(void)	{ return MASTER; }
