inherit "/std/weapon";
#include "/d/Raumdor/defs.h"

/* Sarr */

void
create_weapon()
{
    ::create_weapon();
    set_name("scimitar");
    set_adj("black");
    add_adj("steel");
    set_short("black steel scimitar");
    set_long("This is a smooth edged black scimitar made of steel. It "+
    "has a skull on the bottom of the hilt, and feels very cold to the "+
    "touch. However, the blade looks well maintained and could probably "+
    "do some good damage.\n");
    set_dt(W_SLASH);
    set_hit(30);
    set_pen(21);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_VALUE,1000);
}

