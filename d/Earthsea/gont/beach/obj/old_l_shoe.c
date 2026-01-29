#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("shoe");
    add_adj("old");
    set_short("old left shoe");
    add_adj("left");
    set_long("This is an old shoe, which has holes in the " +
        "toe and sole, made for the left foot. It is not " +
        "much use.\n");
    set_at(A_L_FOOT);
    set_ac(5);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, 5);
}
