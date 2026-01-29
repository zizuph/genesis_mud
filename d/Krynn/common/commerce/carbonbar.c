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
    set_name("carbon");
    add_name(({"carbon","carbon chunk","chunk"}));
    add_pname("carbon chunk´s");
    add_pname(({"carbon", "chunks"}));
    add_pname("carbonchunks");
    set_adj("carbon");
    set_short("carbon chunk");
    set_pshort("carbon chunks");
    set_long("Its a chunk of carbon, the edges are rough as if it was made " +
             "in a hurry, or it was unimportant how it looked.\n");

    my_vol = 15 + random(3) + 1;
    my_val = 30 * my_vol + random(my_vol * 5);
    add_prop(OBJ_I_VALUE, "@@my_value");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, "@@my_volume");

    set_commodity_name ("carbon bar"); // required to link this
                                  // object with the domain server
    set_commodity_value(my_value());
}