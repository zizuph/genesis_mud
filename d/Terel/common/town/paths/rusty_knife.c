/*
    An ordinary knife, worn by travellers. Mortricia 920727
 */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_short("rusty knife");
    set_pshort("rusty knives");
    set_long("It's a simple looking knife.\n");

    set_adj("rusty");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(8);
    set_pen(7);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_KNIFE); /* It's of 'knife' type */
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
