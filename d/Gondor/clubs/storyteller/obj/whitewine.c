/*
 * /d/Gondor/clubs/storytellers/obj/whitewine.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit DRINK_BASE;

void
create_st_drink()
{
    set_soft_amount(300);
    set_alco_amount(12);
    set_name("wine");
    set_adj(({ "white", "glass", "sparkling" }));
    set_short("slender glass of white wine");
    set_pshort("slender glasses of red wine");
    set_long("The slender glass is delicately beautiful, and from within it "+
	"emanates the scent of white wine. The wine sparkles inside the glass, "+
	"making it almost too lovely to drink.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_sip_max_amount(15);
}
