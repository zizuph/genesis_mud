/* Coded the 07/11/98 by Bishop of Calia. This is a polearm
for use by the regular guards of Rust. */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WHIT 30
#define WPEN 35 

public void
create_weapon()
{
    set_name("ranseur");
    add_name("polearm");
    set_adj("steel");
    set_adj("long");

    set_long("This type of polearm is known as a ranseur. It consists" +
        " of a long wooden shaft, with a broad blade at the end. The blade" +
        " is sharpened on both sides, with smaller blades protruding from" +
        " the left and right of the center blade. It would probably be" +
        " used for thrusting.\n");

    set_hit(WHIT + random(4));
    set_pen(WPEN + random(4));
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WHIT, WPEN) - random(300) + 150);
}