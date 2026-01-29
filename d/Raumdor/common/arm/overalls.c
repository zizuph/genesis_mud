#pragma strict_types
#include "defs.h"
inherit "/std/armour";

public void
create_armour()
{
    set_name("overalls");
    set_adj(({"durable","cloth"}));
    set_short("pair of durable cloth overalls");
    set_pshort("pairs of durable cloth overalls");
    set_long("Made of tufted cords, this pair of overalls looks made to " +
        "survive a long day's work.\n");
    set_ac(10 + random(10));
    set_at(A_BODY | A_LEGS);
    add_prop(OBJ_I_WEIGHT, 650);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, SILVER_VALUE * 4);
}
