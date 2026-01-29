
/*
 * psuchae_triangle.c
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
    set_name("black triangle");
    add_name("triangle");
    add_name("_psuchae_triangle_");
    add_adj("black");
    set_short("black triangle");
    set_long("It is a small black triangle. It is very cold to the "+
        "touch and appears to be very important.\n");

    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_M_NO_STEAL,1);
}


