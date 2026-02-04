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
    set_name(({"bluebolt", "sword"}));
    set_short("blue sword");
    set_long("A blue sword, powerful like a bolt from the blue.\n");
    set_adj("blue");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(20);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT, 18000);
    add_prop(OBJ_I_VOLUME, 15000);
    add_prop(OBJ_I_VALUE, 430);
    add_prop(OBJ_M_NO_BUY, 1);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 33, "enchantment" }) );
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_RIGHT);
}
