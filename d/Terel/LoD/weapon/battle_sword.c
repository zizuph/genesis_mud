/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * battle_sword.c
 *
 * used by liuetenants in LoD.
 *
 * dark legion sword Redhawk 921104
 * modified by Sorgum 941025
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
    set_name(({"broadsword","sword"}));
    set_pname(({"broadswords","swords"}));
    add_pname("weapons");

    set_short("blue-steel broadsword");
    set_long("A battle sword that is standard issue in the legion " +
	     "of darkness army.\n");
    set_adj(({"blue-steel","steel","battle"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(30);
    set_pen(25);
    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 3000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_RIGHT); /* You can wield it in any hand. */
}
