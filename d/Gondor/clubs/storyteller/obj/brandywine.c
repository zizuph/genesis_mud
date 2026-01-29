/*
 * /d/Gondor/clubs/storytellers/obj/brandywine.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit DRINK_BASE;

void
create_st_drink()
{
    set_soft_amount(300);
    set_alco_amount(16);
    set_name("wine");
    add_name(({ "glass", "brandywine" }));
    set_adj(({ "glass", "brandy" }));
    set_short("slender glass of brandywine");
    set_pshort("slender glasses of brandywine");
    set_long("The slender glass is delicately beautiful, and from within it "+
	"emanates the delightful scent of brandywine.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_sip_max_amount(15);
}
