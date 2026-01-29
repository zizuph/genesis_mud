/* Coded the 29/10/98 by Bishop of Calia. This is a simple woodsmans
axe for use by the men of Rust. */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WHIT 25
#define WPEN 33

public void
create_weapon()
{
    set_name("axe");
    set_adj("woodsman's");

    set_long("This simple woodsman's axe isn't the weapon of a warrior." +
        " It looks more suited for hewing off the branches of a tree than" +
        " slashing into an opponent. It seems well balanced though, and" +
        " the handle is smooth and would provide good grip.\n");

    set_hit(WHIT);
    set_pen(WPEN);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WHIT, WPEN) - random(300) + 150);
}
