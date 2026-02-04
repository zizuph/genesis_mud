/*
    A black knife, worn by witches. Mortricia 920720
 */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_long("It's black knife. It seems to be very sharp.\n");

    set_adj(({"black"}));
    set_short("black knife");
    set_pshort("black knives");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(15);
    set_pen(15);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_KNIFE); /* It's of 'knife' type */
    set_dt(W_IMPALE);

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
