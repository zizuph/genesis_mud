/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * c_sword.c
 *
 * A sword. Mortricia 931111
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
    set_short("long-bladed sword");
    set_long("A long-bladed sword. Keep away from it!\n");
    set_adj("long-bladed");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(40);
    set_pen(29);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 2000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
