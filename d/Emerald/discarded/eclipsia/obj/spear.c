/* Created by Lucas on October 30, 1995.
 */

inherit "/std/weapon.c";
#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("spear");
    set_short("nymph spear");
    set_long("The sleek spear was used by sea nymphs and merfolk " +
        "of old.  Mermaids are often seen " +
        "carrying the lightweight weapons for self-defense.\n");

    set_hit(25);
    set_pen(25);

    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, 1000 + random (100));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
