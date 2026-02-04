/*
    A blue sword. Mortricia 920722
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("sword");
    set_short("blue sword");
    set_long("A blue sword. Keep away from it!\n");
    set_adj("blue");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(29);
    set_pen(29);
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 4000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
