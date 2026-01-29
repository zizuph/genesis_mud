inherit "/std/weapon";
#include "/sys/wa_types.h"

void
create_weapon()
{
    set_name("rapier");
    set_short("rapier");
    set_adj("light");
    set_adj("beautiful");
    set_long("This rapier is light and nimble. A masters weapon.\n");

    set_hit(30);
    set_pen(20);
    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
}
