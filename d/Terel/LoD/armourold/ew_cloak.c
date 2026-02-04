/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_cloak.c
 *
 * Mergula's cloak.
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <wa_types.h>

create_armour()
{
    set_name("robe");
    set_short("black robe");
    set_long("It's a black robe of finest quality.\n");
    set_adj("black");
    set_default_armour(39, A_ROBE, 0, 0);
    set_am(({ -2, -2, 4}));

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 600);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
    set_likely_cond(12);
}
