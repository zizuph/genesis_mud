/*
 * green moss
 * Boreaulam, September 2012
 */
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/std/object";

void
create_object()
{
    set_name("moss");
    set_adj("green");
    set_short("green moss");
    set_long("This is a green moss. It is rumoured to be a component " +
             "of goblin witch's alchemist recipe.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}

