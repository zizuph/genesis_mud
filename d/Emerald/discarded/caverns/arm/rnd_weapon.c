inherit "/std/weapon";
#include "/sys/wa_types.h"

void
create_weapon()
{

    set_name("rapier");
    set_adj("long");
    set_long("This "+short()+" seems to be a pirates weapon.");

    set_hit(24);
    set_pen(22);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}
