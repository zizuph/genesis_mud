
/*
 * hatchet.c
 * A hatchet, wielded by a citizen of the town of HAven
 * Created by Tibbit, 11 February 1998
 *
 */

inherit "/std/weapon";

#include "../local.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("hatchet");
    set_adj("used");
    add_adj("well");
    add_adj("well-used");
    set_short("well-used hatchet");
    set_pshort("well-used hatchets");

    set_long("A simple hatchet, this tool has been well-used "+
        "over the years.  Despite its long service, "+
        "this small axe continues to do its duty well.\n");

    set_hands(W_ANYH);

    set_dt(W_SLASH);
    set_wt(W_AXE);
    set_hit(13);
    set_pen(18);

}

