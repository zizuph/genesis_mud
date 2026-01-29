/*
 * /d/Gondor/clubs/storytellers/obj/spirits.c
 */
#include "../defs.h"
#include <stdproperties.h>

inherit DRINK_BASE;

void
create_st_drink()
{
    set_soft_amount(150);
    set_alco_amount(40);
    set_name("spirits");
    add_name("spirit");
    set_adj(({ "aged", "dwarven", "cask-aged" }));
    set_short("shot of dwarven spirits");
    set_pshort("shots of dwarven spirits");
    set_long("This is a shot of cask-aged dwarven spirits. The smell of "+
	"oak is barely noticeable under the overwhelming scent of spirits, "+
	"which makes you think this drink is quite strong.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    set_sip_max_amount(10);
}
