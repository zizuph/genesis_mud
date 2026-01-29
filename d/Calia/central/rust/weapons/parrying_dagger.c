/* Coded the 07/11/98 by Bishop of Calia. This is a parrying dagger
for use by the elite guards of Rust. */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WHIT 18
#define WPEN 18

public void
create_weapon()
{
    set_name("dagger");
    set_adj("parrying");
    set_adj("double-bladed");

    set_long("This steel dagger has twin blades sticking out with about" +
        " a thirty degree angle between them. In combat, they could" +
        " be used to parry blows and catch your opponent's weapon." +
        " It has a hilt-basket which would further protect your hand" +
        " in a fight. The metal on the blades has a faint blue tint.\n");

    set_hit(WHIT + random(3));
    set_pen(WPEN + random(3));
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_LEFT);

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WHIT, WPEN) - random(300) + 150);
}
