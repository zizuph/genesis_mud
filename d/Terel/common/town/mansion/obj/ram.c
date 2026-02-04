/* A battering ram, used to break some walls in the Terel mansion */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

#define BSN(xx) break_string(xx + "\n", 70)

void
create_weapon()
{
    set_name("ram");
    add_name("battering ram");
    set_short("heavy battering ram");
    set_long(BSN(
	"It's a heavy battering ram. Suitable for breaking through " +
	"walls."
    ));
    set_adj("heavy");
    set_hit(5);
    set_pen(35);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 26500);
    add_prop(OBJ_I_VOLUME, 12000);
   add_prop("mystic_weapon", 1);
}
