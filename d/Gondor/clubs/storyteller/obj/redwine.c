/*
 * /d/Gondor/clubs/storytellers/obj/redwine.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit DRINK_BASE;

void
create_st_drink()
{
    set_soft_amount(300);
    set_alco_amount(14);
    set_name("wine");
    set_adj(({ "red", "glass", "robust" }));
    set_short("slender glass of red wine");
    set_pshort("slender glasses of red wine");
    set_long("The slender glass is delicately beautiful, and from within it "+
	"emanates the robust scent of red wine.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_sip_max_amount(15);
}
