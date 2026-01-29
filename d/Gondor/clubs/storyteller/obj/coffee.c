/*
 * /d/Gondor/clubs/storytellers/obj/coffee.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit DRINK_BASE;

void
create_st_drink()
{
    set_soft_amount(150);
    set_alco_amount(0);
    set_name("coffee");
    add_name( "cup");
    set_adj(({ "fresh", "freshly brewed", "hot" }));
    set_short("cup of freshly brewed coffee");
    set_pshort("cups of freshly brewed coffee");
    set_long("A hot cup of freshly brewed coffee.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_sip_max_amount(10);
}
