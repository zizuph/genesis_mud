#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("coconut");
    set_adj("fresh");
    set_short("fresh coconut");
    set_long("This coconut looks delectable, as if it had just " +
        "fallen off the tree.\n");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, random(25));
}

public void
special_effect(int num)
{
    write("You break a tooth as you eat the " +
        "coconut" + (num > 1 ? "s " : " ") +
        "with its shell on!\n");
}
