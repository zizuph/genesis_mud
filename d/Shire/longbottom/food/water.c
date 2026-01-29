/*
 * water.c
 * Longbottom drink
 * Finwe, December 2019
 */ 

#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink()
{
    set_name("water");
    set_adj("fresh");

    set_short("glass of water");
    set_pshort("glasses of water");
    set_long("This is a glass of fresh water.");
    set_soft_amount(60);

    add_prop(OBJ_I_VALUE, 0);
}
