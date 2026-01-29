#include <stdproperties.h>

inherit "/std/object";
inherit "/d/Genesis/lib/commodity";

int my_val, my_vol;

int my_value() { return my_val; }
int my_weight() { return my_vol * 10; }
int my_volume() { return my_vol; }

void
create_object()
{
    set_name("scrap");
    add_name(({"leather"}));
    add_pname(({"scraps"}));
    set_adj("leather");
    set_short("leather scrap");
    set_pshort("leather scrap");
    set_long("This is a scrap piece of leather.\n");

    my_vol = 10 + random(3) + 1;
    my_val = 10 * my_vol + random(my_vol * 5);
    add_prop(OBJ_I_VALUE, "@@my_value");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, "@@my_volume");

    set_commodity_name ("leather scrap"); // required to link this
                                  // object with the domain server
    set_commodity_value(my_value());
}
