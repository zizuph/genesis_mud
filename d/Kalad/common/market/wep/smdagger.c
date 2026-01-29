inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

/* A shiny merchant's dagger, by Sarr */

void
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_short("shiny dagger");
    set_long( 
        "This is a long, slim dagger. Its blade shines in the sunlight.\n");
    set_hit(20);
    set_pen(20);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT,800);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE,800);
}

