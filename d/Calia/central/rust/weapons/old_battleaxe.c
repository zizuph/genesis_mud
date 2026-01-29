/* Coded the 6/11/98 by Bishop of Calia. This is Jessups old
battleaxe */

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
    set_name("battleaxe");
    add_name("axe");

    set_adj("old");

    set_long("This old axe might once have been an excellent weapon." +
        " It still looks decent, but age has taken its toll.\n");

    set_hit(WHIT);
    set_pen(WPEN);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WHIT, WPEN) - random(150) + 75);
}