/* created by Aridor, 03/10/94 */
/*
 * Added support for the commerce module in July 2002, by Boron
 */

inherit "/std/object";
inherit "/d/Genesis/lib/commodity";

#include "../local.h"

int my_val, my_vol;

int my_value() { return my_val; }
int my_weight() { return my_vol * 21 / 2; }
int my_volume() { return my_vol; }

void
create_object()
{
    set_name("silverpiece");
    add_name("piece of silver");
    add_pname("pieces of silver");
    add_pname("pieces");
    add_pname("silverpieces");
    add_pname("nuggets");
    add_name("piece");
    add_name("nugget");
    set_adj("silver");
    set_short("piece of silver");
    set_pshort("pieces of silver");
    set_long("It's a piece of real silver! It shines brightly and lets your " +
         "eyes sparkle.\n");
    my_vol = random(8) + random(6) + 1;
    my_val = 5 * my_vol + random(my_vol);
    add_prop(OBJ_I_VALUE, "@@my_value");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, "@@my_volume");

    set_commodity_name ("silverpiece"); // required to link this
                                     // object with the domain server
    set_commodity_value(my_value());
}

