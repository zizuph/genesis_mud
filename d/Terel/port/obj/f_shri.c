/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * f_shri.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDFOOD;

create_food()
{
    ::create_food();
    set_name("shrimps");
    set_pname("shrimps");
    set_adj("fried");
    set_long("Some fried shrimps. They look crunchy.\n");
    set_amount(5);
    add_prop(OBJ_I_WEIGHT, 19);
    add_prop(OBJ_I_VOLUME, 18);
}
