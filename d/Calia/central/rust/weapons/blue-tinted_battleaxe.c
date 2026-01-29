/* Coded the 07/11/98 by Bishop of Calia. This is a one-handed
battleaxe for use by the elite guards of Rust. */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WHIT 32
#define WPEN 32 

public void
create_weapon()
{
    set_name("battleaxe");
    add_name("axe");
    set_adj("blue-tinted");
    set_adj("jagged");

    set_long("The blade of this battleaxe has been tinted with a light" +
        " blue colour. It doesn't look new, but is in excellent condition" +
        " still. The blade razor-sharp, and the wooden handle kept neat" +
        " and polished. It's obviously a warrior's weapon, made for slicing" +
        " through flesh and bone.\n");

    set_hit(WHIT + random(4));
    set_pen(WPEN + random(4));
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);

    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WHIT, WPEN) - random(300) + 150);
}