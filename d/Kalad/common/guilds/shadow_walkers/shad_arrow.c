inherit "/d/Kalad/std/missile_std";
#include "/d/Kalad/defs.h"

void
create_missile()
{
    set_name("arrow");
    add_adj(({"steel-tipped","wooden"}));
    set_short("steel-tipped wooden arrow");
    set_long("This is a long and deadly looking arrow made of black "+
    "oak mounted with a razor-sharp steel head.\n");
    set_missile_type("arrow");
    set_hit(5);
    set_pen(5);
}

