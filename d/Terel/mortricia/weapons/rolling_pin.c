/*
    A rolling pin, can be used as a club ;-) Mortricia 920729
 */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_weapon()
{
    set_name("pin");
    set_short("rolling pin");
    set_long("A rolling pin, somewhat doughy.\n");

    set_adj(({"rolling", "doughy"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(10);
    set_pen(10);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH);
}
