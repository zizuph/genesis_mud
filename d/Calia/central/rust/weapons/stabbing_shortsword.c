/* Coded the 07/11/98 by Bishop of Calia. This is a one-handed
shortsword for use by the elite guards of Rust. */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WHIT 30
#define WPEN 30 

public void
create_weapon()
{
    set_name("shortsword");
    add_name("sword");
    set_adj("basket-hilt");
    set_adj("thin");

    set_long("This shortsword has a thin, yet rigid blade." +
        " It looks well suited for an agile fighter, doing quick" +
        " stabbing attacks.\n");

    set_hit(WHIT + random(4));
    set_pen(WPEN + random(4));
    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WHIT, WPEN) - random(300) + 150);
}