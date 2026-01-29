/*
 * Food item cloned for halfling guild
 * Finwe, January 2016
 */

inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_name("mead");
    set_adj("sweet");
    set_short("flask of sweet mead");
    set_pshort("flasks of sweet mead");
    set_long("This is a " + query_short() + ". It is clear with a sligh " +
        "yellow color. The drink is made of fermented honey and water and " +
        "has a sweet taste.\n");
    set_soft_amount(110);
    set_alco_amount(10);
    add_prop(OBJ_I_WEIGHT, 473);
    add_prop(OBJ_I_VOLUME, 473);
}