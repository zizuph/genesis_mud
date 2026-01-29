
/*
 * diabrecho_triangle.c
 *
 * An object for the Spirit Circle of Psuchae guru quest
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
#include SPIRIT_HEADER

void
create_object()
{
    set_name("blue triangle");
    add_name("triangle");
    add_name("_diabrecho_triangle_");
    add_adj("blue");
    set_short("blue triangle");
    set_long("It is a small blue triangle. It is quite cool to the "+
        "touch and when you put it near your ear, you can hear what "+
        "sounds like water splashing around inside of it. It appears "+
        "to be very important.\n");

    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_M_NO_STEAL,1);
}


