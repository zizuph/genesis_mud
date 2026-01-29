inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"


void
create_weapon()
{
    ::create_weapon();
    set_name("club");
    set_short("heavy iron club");
    set_long("A heavy iron club.\n");
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hit(8);
    set_pen(12);
}

