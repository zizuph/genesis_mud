inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"


void
create_weapon()
{
    ::create_weapon();
    set_name("knife");
    set_adj(({"black","jagged"}));
    set_short("black jagged knife");
    set_long("A nasty knife.\n");
    set_wt(W_KNIFE);
    set_dt(W_SLASH);
    set_hit(6);
    set_pen(10);
}

