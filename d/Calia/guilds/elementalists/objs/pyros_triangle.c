
/*
 * pyros_triangle.c
 *
 * An object for the Elemental Clerics guru quest
 *
 * Copyright (C): Jaacar, August 23rd, 2003
 *
 */


#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

void
create_object()
{
    set_name("fiery triangle");
    add_name("triangle");
    add_name("_pyros_triangle_");
    add_adj("fiery");
    set_short("fiery triangle");
    set_long("It is a small fiery triangle. It appears as though "+
        "it is on fire, yet it really is not. It is warm to the touch, "+
        "but not enough to burn your hands. It appears to be very "+
        "important.\n");

    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_M_NO_STEAL,1);
}


