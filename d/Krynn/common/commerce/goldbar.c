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
    set_name("goldbar");
    add_name(({"gold","gold bar","bar"}));
    add_pname("gold bars");
*/
    set_name("bar");
    add_name(({"goldbar"}));
    add_pname("bars");
    add_pname(({"gold", "bars"}));
    add_pname("goldbars");
    set_adj("gold");
    set_short("gold bar");
    set_pshort("gold bars");
    set_long("Its a solid bar, the edges are rough as if it was made " +
             "in a hurry, or it was unimportant how it looked.\n");

    my_vol = 15 + random(3) + 1;
    my_val = 100 * my_vol + random(my_vol * 5);
    add_prop(OBJ_I_VALUE, "@@my_value");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, "@@my_volume");

    set_commodity_name ("gold bar"); // required to link this
                                  // object with the domain server
    set_commodity_value(my_value());
}
