#pragma strict_types

inherit "/std/receptacle.c";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_receptacle()
{
    set_short("steel-plated footlocker");
    set_name("footlocker");
    add_name("locker");
    set_adj("steel-plated");
    add_adj("steel");
    add_adj("plated");
    set_long("This steel-plated footlocker rests on the floor near the north " +
        "entrance. A lidless eye is painted on its top. ");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The footlocker is fixed to the floor, " +
        "you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 750000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);

}
