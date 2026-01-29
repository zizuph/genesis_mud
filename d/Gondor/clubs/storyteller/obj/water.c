/*
 * /d/Gondor/clubs/storytellers/obj/water.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit DRINK_BASE;

void
create_st_drink()
{
    set_soft_amount(150);
    set_alco_amount(0);
    set_name("water");
    add_name( "glass");
    set_adj(({ "glass", "water" }));
    set_short("glass of water");
    set_pshort("glasses of water");
    set_long("A small glass of cold water.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_sip_max_amount(5);
}
