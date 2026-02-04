/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_drink.c
 *
 * Mergula's drink of choice.
 */

inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("rum");
    set_long("The liquid is clear and strong.\n");
    set_soft_amount(100);
    set_alco_amount(88);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
