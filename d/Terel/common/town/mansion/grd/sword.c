/* A weapon should always begin with these statements: */

inherit "/std/weapon";
#include "/d/Terel/common/terel_std_rec.h"
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_weapon()
{
    /* Set the name, short description and long description */
    set_name("rapier");
    set_short("gleaming rapier"); 
    set_long("A gleaming long rapier.\n");
    set_adj("gleaming");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(35);
    set_pen(20);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD); /* It's of 'knife' type */
    set_dt(W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
