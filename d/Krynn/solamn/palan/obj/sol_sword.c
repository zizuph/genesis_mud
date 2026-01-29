/* created by Aridor 09/15/94 */

inherit "/std/weapon";

#include "../local.h"
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("longsword");
    set_adj("solamnic");
    add_adj("two-handed");
    add_name("sword");
    set_short("solamnic two-handed longsword");
    set_pshort("solamnic two-handed longswords");
    set_long("This is the pride of a Solamnic Knight. It is a weapon of " +
	     "excellent quality. It is polished to shine so brightly " +
	     "that it almost hurts your eyes.\n");

    set_hit(36);
    set_pen(36);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6000);

}

