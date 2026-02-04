inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>


public void
create_weapon()
{

    set_name("shovel");
     set_adj("simple");
    set_short("simple shovel");
    set_long("It looks to be a simple shovel.\n");

    set_keep();

    set_hit(2 + random(3));
    set_pen(5 + random(3));

    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);

    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME,  700);
}

