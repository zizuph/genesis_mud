/*
 * Food item cloned for halfling guild
 * Finwe, January 2016
 */

inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("wine");
    set_adj("sweet");
    set_short("bottle of sweet wine");
    set_pshort("bottles of sweet wine");
    set_long("This is a small bottle of sweet wine. It is a garnet red " +
        "with floral hints and sweet berries.\n");
    set_soft_amount(100);
    set_alco_amount(20);
    add_prop(OBJ_I_WEIGHT, 473);
    add_prop(OBJ_I_VOLUME, 473);
}