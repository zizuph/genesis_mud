
/*
 * knife.c
 * A paring knife, wielded by a merchant of the town of HAven
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
    set_name("knife");
    set_adj("paring");
    add_adj("small");
    set_short("small paring knife");
    set_pshort("small paring knives");

    set_long("You hold a useful tool, a small paring "+
        "knife, used for cutting and trimming fruits and "+
        "vegetables.\n");

    set_hands(W_ANYH);

    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_KNIFE);
    set_hit(8);
    set_pen(11);

}

