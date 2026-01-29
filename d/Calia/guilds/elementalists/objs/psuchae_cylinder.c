
/*
 * psuchae_cylinder.c
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
    set_name("glowing cylinder");
    add_name("_psuchae_cylinder_");
    add_name("cylinder");
    add_adj("glowing");
    set_short("glowing cylinder");
    set_long("It is a small glowing cylinder. You cannot figure out "+
        "why it is glowing, it must be some type of magic deep inside "+
        "of it causing it to do so.\n");

    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_M_NO_STEAL,1);
}


