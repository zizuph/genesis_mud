/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * An bag.
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/container";

create_container()
{
    set_name("bag");
    set_short("leather bag");
    set_long("It's a high quality leather bag.\n");
    set_adj(({"leather"}));

    add_prop(OBJ_I_VALUE, 100 + random(20));

    add_prop(CONT_I_WEIGHT,     600);
    add_prop(CONT_I_MAX_WEIGHT, 8000);
    add_prop(CONT_I_VOLUME,     500);
    add_prop(CONT_I_MAX_VOLUME, 8000);
    add_prop(CONT_I_TRANSP,     1);
    add_prop(CONT_I_RIGID,      0);
}
