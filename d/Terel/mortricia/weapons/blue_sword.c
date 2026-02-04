/*
    A blue sword. Mortricia 920722
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("sword");
    set_short("blue sword");
    set_long("A blue sword. Keep away from it!\n");
    set_adj("blue");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(34);
    set_pen(34);
    add_prop(OBJ_I_WEIGHT, 14000);
    add_prop(OBJ_I_VOLUME, 6000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
