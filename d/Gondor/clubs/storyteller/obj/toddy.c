/*
 * /d/Gondor/clubs/storytellers/obj/toddy.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit DRINK_BASE;

void
create_st_drink()
{
    set_soft_amount(150);
    set_alco_amount(25);
    set_name("toddy");
    add_name("rum");
    set_adj(({ "hot", "rum" }));
    set_short("glass of hot rum toddy");
    set_pshort("glasses of hot rum toddy");
    set_long("This is a warm drink, from which you can smell the "+
	"scent of rum, as well as some sugar and spices.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_sip_max_amount(10);
}
