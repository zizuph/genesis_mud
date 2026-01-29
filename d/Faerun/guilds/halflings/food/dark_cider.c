/*
 * Food item cloned for halfling guild
 * Finwe, January 2016
 */

inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("cider");
    set_adj("flask");
    set_adj("dark");
    set_short("flask of dark cider");
    set_pshort("flasks of dark cider");
    set_long("This is a flask of dark apple cider. It was made by pressing " +
        "apples to squeeze out the juice. The cider is cloudy with small " +
        "bits of apple floating in it.\n");
    set_soft_amount(100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
