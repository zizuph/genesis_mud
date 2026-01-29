/* A test weapon, coded september 19th, 1998 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>

#define WHIT 60
#define WPEN 60

public void
create_weapon()
{
    set_name("ball");
    set_adj("wrecking");
    set_long("This is an huge iron ball fastened to a 10 foot" +
        " long chain. Something a gargantuan dogcow might use\n");
    set_hit(WHIT);
    set_pen(WPEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(OBJ_I_VOLUME, 30000);
}
