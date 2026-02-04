/*
    A black knife, worn by witches. Mortricia 920720
 */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    add_name("weapon");
    add_pname("weapons");
    set_pshort("black knives");
    set_short("black knife");
    set_long("It's black knife. It seems to be very sharp.\n");

    set_adj(({"black", "sharp"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(18);
    set_pen(20);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_KNIFE); /* It's of 'knife' type */
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
