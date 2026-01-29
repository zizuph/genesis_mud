#pragma strict_types
#pragma save_binary

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("axe");
    set_adj("impressive");

    set_short("impressive axe");
    set_long("The axe has a very sharp, shiny edge.\n");

    set_hit(20);
    set_pen(20);

    set_wt(W_AXE);

    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
}

