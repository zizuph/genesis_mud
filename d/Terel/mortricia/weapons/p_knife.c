/*
    A knife. Mortricia 920720
 */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_short("beautiful knife");
    set_pshort("beautiful knives");
    set_long("It's a beautiful knife, almost like a souvenir.\n");

    set_adj(({"beautiful"}));

    set_hit(17);
    set_pen(12);

    set_wt(W_KNIFE);
   set_dt(W_IMPALE);

    set_hands(W_ANYH); /* You can wield it in any hand. */
}
