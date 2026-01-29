/*
 * whiskey.c
 * Longbottom drink
 * finwe, December 30, 2019
 */ 

#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink()
{
    set_name("whiskey");
    add_name("whisky");
    set_adj("strong");

    set_long("This is a glass of strong whiskey. It was distilled from " +
        "corn in the region of Longbottom in the Shire.");
    set_soft_amount(30);
    set_alco_amount(40);

    add_prop(OBJ_I_VALUE, 0);
}
