/*
    An ordinary scythe, used by farmers. Mortricia 920729
 */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_weapon()
{
    set_name("scythe");
    set_short("ordinary scythe");
    set_long("It's an ordinary scythe, but it is sharp.\n");

    set_adj("ordinary");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(25);
    set_pen(20);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);

    /* Last, how shall it be wielded? */
    set_hands(W_BOTH);
}
