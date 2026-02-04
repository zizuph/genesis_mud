/*
    A balancing rod, used by tight-rope dancers.
 */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_weapon()
{
    set_name("rod");
    set_short("long rod");
    set_long("It's a long rod. It's made out of wood.\n");

    set_adj(({"long"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(8);
    set_pen(12);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_POLEARM); /* It's of 'polearm' type */
    set_dt(W_IMPALE | W_BLUDGEON);

    /* Last, how shall it be wielded? */
    set_hands(W_BOTH);
    add_prop("mystic_weapon", 1);
}
