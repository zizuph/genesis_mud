inherit "/d/Kalad/std/missile_std";
#include "/d/Kalad/defs.h"

void
create_missile()
{
    set_name("quarrel");
    add_adj(({"deadly","steel"}));
    set_short("deadly steel quarrel");
    set_long("This is a short black steel bolt with a razor-shapr "+
    "tip that could punch through armour.\n");
    set_missile_type("quarrel");
    set_hit(5);
    set_pen(10);
}

