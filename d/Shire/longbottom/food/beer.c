/*
 * beer.c
 * Longbottom drink
 * Finwe, December 2019
 */ 

#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink()
{
    set_name("beer");
    set_adj("cold");

    set_short("cold beer");
    set_long("This is a glass of beer. It looks cool and refreshing, " +
        "and a pale, yellow color.");
    set_soft_amount(75);
    set_alco_amount(10);

    add_prop(OBJ_I_VALUE, 0);
}
