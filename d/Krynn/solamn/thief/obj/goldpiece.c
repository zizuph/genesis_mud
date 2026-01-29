/* created by Aridor, 03/10/94 */
/*
 * Added support for the commerce module in July 2002, by Boron
 */

inherit "/std/object";
inherit "/d/Genesis/lib/commodity";


#include "../local.h"

int my_val, my_vol;

int my_value() { return my_val; }
int my_weight() { return my_vol * 19; }
int my_volume() { return my_vol; }

void
create_object()
{
    set_name("goldpiece");
    add_name("piece of gold");
    add_pname("pieces of gold");
    add_pname("pieces");
    add_pname("goldpieces");
    add_pname("nuggets");
    add_name("piece");
    add_name("nugget");
    set_adj("gold");
    set_short("piece of gold");
    set_pshort("pieces of gold");
    set_long("It's a piece of real gold! You could call it a gold nugget.\n");
    my_vol = random(4) + random(3) + 1;
    my_val = 110 * my_vol + random(my_vol * 5);
    add_prop(OBJ_I_VALUE, "@@my_value");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, "@@my_volume");

    set_commodity_name ("goldpiece"); // required to link this
                                     // object with the domain server
    set_commodity_value(my_value());
}


