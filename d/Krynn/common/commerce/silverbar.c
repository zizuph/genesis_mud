/*
 * Created and added support for the commerce module in July 2002, by Boron
 */

#include <stdproperties.h>

inherit "/std/object";
inherit "/d/Genesis/lib/commodity";

int my_val, my_vol;

int my_value() { return my_val; }
int my_weight() { return my_vol * 19; }
int my_volume() { return my_vol; }

void
create_object()
{
/*
    set_name("silverbar");
    add_name(({"silver","silver bar","bar"}));
    add_pname("silver bars");
*/
    set_name("bar");
    add_name(({"silverbar"}));
    add_pname(({ "bars"}));
    add_pname("silverbars");
    set_adj("silver");
    set_short("silver bar");
    set_pshort("silver bars");
    set_long("Its a solid bar, the edges are rough as if it was made " +
             "in a hurry, or it was unimportant how it looked.\n");

    my_vol = 15 + random(3) + 1;
    my_val = 50 * my_vol + random(my_vol * 5);
    add_prop(OBJ_I_VALUE, "@@my_value");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, "@@my_volume");

    set_commodity_name ("silver bar"); // required to link this
                                  // object with the domain server
    set_commodity_value(my_value());
}
