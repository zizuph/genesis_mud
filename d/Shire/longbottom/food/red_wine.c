/*
 * red_wine.c
 * Longbottom drink
 * Finwe, December 2019
 */ 

#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink()
{
    set_name("wine");
    set_adj("cold");
    set_adj("red");

    set_short("glass of red wine");
    set_long("This is a glass of red wine, also known as Old Winyard. " +
        "It comes from the South Farthling in the Shire. The wine is " +
        "known for being strong, and is highly regarded as one of " +
        "the best wines.");
    set_soft_amount(40);
    set_alco_amount(80);

    add_prop(OBJ_I_VALUE, 0);
}
