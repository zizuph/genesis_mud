
/*
 * pyros_staff.c
 *
 * An object for the Spirit Circle of Psuchae entrance quest
 *
 * Copyright (C): Jaacar, September 4th, 2003
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
#include SPIRIT_HEADER

void
create_object()
{
    set_name("red staff");
    add_name("staff");
    add_name("_pyros_staff_");
    add_adj("red");
    set_short("red staff");
    set_long("It is a long red staff topped with a shining fire "+
        "opal. It is very warm to the touch and appears to be "+
        "very important.\n");

    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_ELEMENTAL_STAFF,1);
    add_prop(OBJ_M_NO_STEAL,1);
}

string
query_auto_load()
{
    return MASTER + ":";
}
