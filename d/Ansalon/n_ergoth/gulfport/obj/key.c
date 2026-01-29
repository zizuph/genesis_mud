
/*
 * key.c
 * A key, to the old sailor's hidden whiskey stash
 * Town of Gulfport, Northern Ergoth
 * Tibbit, 30 April 1998
 *
 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("key");
    add_name("_whiskey_quest_key_");
    set_adj("simple");
    add_adj("silver");

    set_short("simple silver key");
    set_pshort("simple silver keys");
    set_long("A tiny silver key, quite simple "+
        "in construction, with no special markings or "+
        "distinguishing features.  "+
        "You wonder at its use.\n");

    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 42);

}

