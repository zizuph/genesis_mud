/* created by Boron and added support for
 * the commerce module in July 2002, by Boron
 */

inherit "/std/object";
inherit "/d/Genesis/lib/commodity";

#include "../local.h"

int my_val, my_vol;

int my_value() { return my_val; }
int my_weight() { return my_vol * 25 / 2; }
int my_volume() { return my_vol; }

void
create_object()
{
    set_name("piece of carbon ore");
    add_name("carbon ore");
    add_name("carbon");
    add_pname("pieces");
    add_pname("carbonpieces");
    add_pname("ores");
    add_name("ore");
    set_adj("carbon");
    add_pname("pieces of carbon ore");
    set_short("piece of carbon ore");
    set_pshort("pieces of carbon ore");
    set_long("It's a piece of carbon ore! It glitters in the light even " +
         "though it is in fact black.\n");
    my_vol = random(8) + random(16) + 1;
    my_val = my_vol + random(my_vol / 5);
    add_prop(OBJ_I_VALUE, "@@my_value");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, "@@my_volume");

    set_commodity_name ("carbonpiece"); // required to link this
                                     // object with the domain server
    set_commodity_value(my_value());
}

