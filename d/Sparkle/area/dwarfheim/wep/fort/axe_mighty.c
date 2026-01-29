#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("axe");
    set_adj("mighty");

    set_short("mighty axe");
    set_long("This is a very expensive battle axe, manufactured for the Dwarf King.\n");

    set_hit(30);
    set_pen(30);

    set_wt(W_AXE);

    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
}

