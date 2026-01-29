/*
 * /d/Gondor/guilds/rangers/obj/water.c
 */
inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_name("water");
    set_pname("waters");
    add_pname(({"glasses", "glasses of water"}));
    set_adj("fresh");
    set_short("glass of fresh water");
    set_pshort("glasses of fresh water");
    set_long("A glass of fresh water drawn from a nearby spring. It " +
        "looks like it would quench your thirst.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(100);
    set_alco_amount(0);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
