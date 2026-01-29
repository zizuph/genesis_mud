/* Created by Lucas on October 30, 1995.
 */

inherit "/std/weapon.c";
#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("trident");
    set_short("silver trident");
    set_long("The three-pronged trident looks like a very fierce " +
        "weapon indeed.  The silver points gleam in the light " +
        "shining through the deep waters.\n");
    set_adj("silver");

    set_hit(25);
    set_pen(25);

    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_BLUDGEON);
    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, 1000 + random (100));
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
}
