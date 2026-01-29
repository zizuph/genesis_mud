
/*
 * pitchfork.c
 * A pitchfork, wielded by a citizen of the town of HAven
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
    set_name("pitchfork");
    set_adj("bent");
    add_adj("slightly");
    set_short("slightly bent pitchfork");
    set_pshort("slightly bent pitchforks");

    set_long("This pitchfork, a handy tool on the farm, "+
        "is slightly bent, although still in good shape.\n");

    set_hands(W_BOTH);

    set_dt(W_IMPALE);
    set_wt(W_POLEARM);
    set_hit(20);
    set_pen(21);

}

