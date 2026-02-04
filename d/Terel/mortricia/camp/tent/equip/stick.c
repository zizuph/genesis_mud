/* A wooden stick, for kids really */
inherit "/std/weapon";
#include "/sys/wa_types.h"

void
create_weapon()
{
    set_name("stick");
    set_short("wooden stick");
    set_long("It's a wooden stick. Not much of a weapon really.\n");
    set_adj("wooden");
    set_hit(3);
    set_pen(3);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON | W_IMPALE);
    set_hands(W_BOTH);
}
