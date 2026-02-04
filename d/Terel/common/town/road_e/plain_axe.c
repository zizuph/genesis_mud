/*
    A plain axe. Mortricia 920729
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("axe");
    set_short("plain axe");
    set_long("It's a plain axe, not dull though.\n");
    set_adj("plain");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(25);
    set_pen(27);
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 12000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
