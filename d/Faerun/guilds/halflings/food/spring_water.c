/*
 * Food item cloned for halfling guild
 * Finwe, January 2016
 */

inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("water");
    set_adj("spring");
    set_short("flask of spring water");
    set_pshort("flasks of spring water");
    set_long("This is a flask of spring water. It is crisp and cool, and " +
        "looks very refreshing.\n");
    set_soft_amount(100);
    add_prop(OBJ_I_WEIGHT, 473);
    add_prop(OBJ_I_VOLUME, 473);
}
