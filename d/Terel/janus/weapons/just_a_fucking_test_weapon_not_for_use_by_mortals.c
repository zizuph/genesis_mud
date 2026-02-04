/* A weapon should always begin with these statements: */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include <stdproperties.h>

void
create_weapon()
{
    /* Set the name, short description and long description */
    set_name("stormbringer");
    set_short("Stormbringer"); /* Observe, not 'a small dagger' */
    set_long("A black broadsword with a strong evil aura.\n");

    /* Now, a player can refere to this weapon as 'weapon' and 'dagger'. To
     * distinguish it from other daggers, we want the player to be able to 
     * use 'small dagger' as an id too.
     */
    set_adj("");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(60);
    set_pen(60);
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,180);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD); /* It's of 'knife' type */
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
