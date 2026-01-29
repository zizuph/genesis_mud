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
    set_name("piece of iron ore");
    add_name("iron ore");
    add_name("iron");
    add_pname("pieces");
    add_pname("ironpieces");
    add_pname("ores");
    add_name("ore");
    set_adj("iron");
    add_pname("pieces of iron ore");
    set_short("piece of iron ore");
    set_pshort("pieces of iron ore");
    set_long("It's a piece of iron ore! It glitters in the light even " +
         "though it is in fact black.\n");
    my_vol = random(8) + random(16) + 1;
    my_val = my_vol + random(my_vol / 5);
    add_prop(OBJ_I_VALUE, "@@my_value");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, "@@my_volume");

    set_commodity_name ("ironpiece"); // required to link this
                                     // object with the domain server
    set_commodity_value(my_value());
}

