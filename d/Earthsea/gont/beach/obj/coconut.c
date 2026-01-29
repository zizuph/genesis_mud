#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("coconut");
    set_adj("migratory");
    set_short("migratory coconut");
    set_long("This appears to be a coconut that has travelled " +
        "far on watery currents to get to these shores.\n");
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
