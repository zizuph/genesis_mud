/* Created by Karath
 */

inherit "/std/weapon.c";
#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("trident");
    set_short("coral-encrusted trident");
    set_long("The three-pronged trident looks like a deadly " +
        "weapon indeed. It appears to be made of silver, but it " +
	"has twisting growths of coral all over it. The coral "+
	"is quite sharp, and just a tickle looks like it would "+
	"rip open skin.\n");
    set_adj("coral-encrusted");

    set_hit(29);
    set_pen(33);

    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
}
