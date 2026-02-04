/*
    A plain sword. Mortricia 920729
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("sword");
    set_short("plain sword");
    set_long("It's a plain sword, not dull though.\n");
    set_adj("plain");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(26);
    set_pen(26);
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 12000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
