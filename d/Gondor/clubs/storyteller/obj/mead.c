/*
 * /d/Gondor/clubs/storytellers/obj/mead.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit DRINK_BASE;

void
create_st_drink()
{
    set_soft_amount(400);
    set_alco_amount(8);
    set_name("mead");
    add_name(({ "mug" }));
    set_adj(({ "sweet", "spiced" }));
    set_short("mug of spiced mead");
    set_pshort("mugs of spiced mead");
    set_long("The mug contains a fair amount of mead, which has "+
	"been sweetened and spiced to give it a delicious aroma.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_sip_max_amount(20);
}
