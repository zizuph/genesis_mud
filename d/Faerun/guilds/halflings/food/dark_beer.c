/*
 * Food item cloned for halfling guild
 * Finwe, January 2016
 */

inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("beer");
    set_adj("dark");
    set_short("bottle of dark beer");
    set_pshort("bottles of dark beer");
    set_long("This is a small bottle of dark beer. It looks refreshing " +
        "and smells strong.\n");
    set_soft_amount(110);
    set_alco_amount(5);
    add_prop(OBJ_I_WEIGHT, 473);
    add_prop(OBJ_I_VOLUME, 473);
}