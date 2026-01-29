/* Coded the 29/10/98 by Bishop of Calia. This is a simple broomstick
axe for use by the housewifes of Rust. */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WHIT 20
#define WPEN 20

public void
create_weapon()
{
    set_name("broom");
    set_adj("wooden");
    set_adj("long");

    set_long("This broomstick looks like a great tool for cleaning up" +
        " a mess, as well as getting a lazy husband to work.\n");

    set_hit(WHIT);
    set_pen(WPEN);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WHIT, WPEN) - random(150) + 75);
}