/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * plain_sword.c
 *
 * A plain sword. Mortricia 920729
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>
#include <formulas.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    ::create_weapon();
    set_name("sword");
    set_short("plain sword");
    set_long("It's a plain sword, not dull though.\n");
    set_adj("plain");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(20);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 9000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
