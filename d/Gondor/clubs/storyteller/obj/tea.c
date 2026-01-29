/*
 * /d/Gondor/clubs/storytellers/obj/tea.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit DRINK_BASE;

void
create_st_drink()
{
    set_soft_amount(300);
    set_alco_amount(0);
    set_name("cup");
    add_name(({ "tea", "lemon tea", "hot tea" }));
    set_adj(({ "tea", "hot", "lemon" }));
    set_short("cup of hot tea with lemon");
    set_pshort("cups of hot tea with lemon");
    set_long("The smell of hot tea mixes with the pleasant scent of "+
	"lemons to create a delightful aroma around this beverage. It "+
	"looks like it will taste as good as it smells.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_sip_max_amount(10);
}
