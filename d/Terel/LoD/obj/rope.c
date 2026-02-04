/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * rope.c
 *
 */
inherit "/std/rope";

#include "/d/Terel/include/Terel.h"

public void
create_rope()
{
    set_name("rope");
    set_adj("long");

    set_long("It's some plain rope. It seems to be of high-quality.\n");

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 34);
}

