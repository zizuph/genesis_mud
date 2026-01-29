/* A test weapon, coded september 19th, 1998 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WHIT 40
#define WPEN 35

public void
create_weapon()
{
    set_name("spear");
    set_adj(({"broad", "jagged"}));
    set_long("At first glance, the blade of this spear seems" +
        " poorly forged, with protrusions sticking this way and" +
        " that. However, close study makes it apparent" +
        " that it has been made this way for a purpose. You can" +
        " picture scoring some nasty hits with it.\n");
    set_hit(WHIT);
    set_pen(WPEN);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 4500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WHIT, WPEN) - random(300) + 150);
}
